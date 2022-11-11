#include <Pataro/Engine.hpp>

#include <Pataro/Constants.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Utils.hpp>
#include <Pataro/Map/Room.hpp>
#include <Pataro/Map/Constants.hpp>
#include <Pataro/Components/AI/Player.hpp>
#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Destructible/Player.hpp>
#include <Pataro/Components/Container.hpp>

#include <SDL.h>
#include <libtcod.hpp>

#include <utility>
#include <fstream>

using namespace pat;

Engine::Engine(unsigned width, unsigned height, const std::string& title, bool show_debug) :
    m_width(width), m_height(height), m_running(true), m_show_debug(show_debug), m_console(width, height)
{
    TCOD_ContextParams params {};
    params.tcod_version = TCOD_COMPILEDVERSION;
    params.window_title = title.c_str();
    params.console = m_console.get();
    params.vsync = true;
    params.renderer_type = TCOD_RENDERER_SDL2;

    m_context = tcod::Context(params);

    reset();
}

void Engine::reset()
{
    m_state = GameState::StartUp;

    // create the player
    m_player = std::make_shared<Entity>(0, 0, '@', "Player", colors::white);
    m_player->set_ai<component::PlayerAI>();
    m_player->set_attacker<component::Attacker>(5.f);
    m_player->set_destructible<component::PlayerDestructible>(30.f, 2.f, "your cadaver");
    m_player->set_container<component::Container>(26);  ///< One slot per letter in the alphabet

    // instantiate a map with 1 level(s)
    m_map = std::make_unique<Map>(map::details::level_w, map::details::level_h, 1);
    m_map->current_level().enter(m_player);

    // setup gui
    Gui::Proxy_t proxy_player_hp = [this](float* val, float* max_val) -> void {
        *val     = m_player->destructible()->hp();
        *max_val = m_player->destructible()->max_hp();
    };
    m_gui = std::make_unique<Gui>(m_width, 7, proxy_player_hp);

    m_gui->message(colors::red, "Welcome stranger!\nPrepare to perish in the Tombs of the Ancient Kings.");
}

void Engine::update()
{
    if (m_state == GameState::StartUp)
        m_map->compute_fov(m_player->get_x(), m_player->get_y(), details::player_fov);
    else if (m_state != GameState::Defeat)
        m_state = GameState::Idle;

    handle_events();

    // player actions only activated if we haven't lost
    if (m_state != GameState::Defeat)
    {
        std::unique_ptr<Action> action = m_player->update(this);
        if (action)
            action->perform(this);
    }

    switch (m_lastkey)
    {
        case SDLK_F3:
        {
            // FIXME
            // int width = 0;
            // int height = 0;
            // TCOD_ColorRGBA* pixels = TCOD_context_screen_capture_alloc(m_context.get_ptr().get(), &width, &height);
            // lodepng_encode32_file(
            //     ("screenshot_" + details::date_to_string() + ".png").c_str(),
            //     reinterpret_cast<unsigned char*>(pixels),
            //     static_cast<unsigned>(width),
            //     static_cast<unsigned>(height)
            // );
            // free(pixels);
            break;
        }

        case SDLK_UP:
        case SDLK_LEFT:
            if (m_state == GameState::Defeat)
                m_scroll_pos = m_scroll_pos <= 0 ? 0 : m_scroll_pos - 1;
            break;

        case SDLK_DOWN:
        case SDLK_RIGHT:
            if (m_state == GameState::Defeat)
                m_scroll_pos = m_scroll_pos + 1 >= static_cast<int>(m_log.size()) ? static_cast<int>(m_log.size()) - 1 : m_scroll_pos + 1;
            break;

        case SDLK_ESCAPE:
            if (m_state == GameState::Defeat)
                reset();
            break;

        default:
            break;
    }

    // if it's a new turn, update all the Entities
    if (m_state == GameState::NewTurn)
        m_map->update(this);
}

void Engine::render()
{
    float dt = m_timer.sync(30);

    TCOD_console_clear(m_console.get());

    m_map->render(this, dt);
    m_gui->render(this, m_console.get(), 0, m_height - m_gui->get_height());

    if (m_show_debug)
        tcod::print(m_console, {0, 0}, tcod::stringf("%.2f ms", dt * 1000), std::nullopt, std::nullopt);

    // defeat ui
    if (m_state == GameState::Defeat)
    {
        static const int UI_WIDTH = 50, UI_HEIGHT = 28;
        static tcod::Console con(UI_WIDTH, UI_HEIGHT);

        tcod::draw_frame(con, {0, 0, UI_WIDTH, UI_HEIGHT}, details::frame, tcod::ColorRGB(50, 180, 200), std::nullopt, TCOD_BKGND_DEFAULT);

        // display the items with their keyboard shortcut
        int y = 1;

        for (const auto& pair : m_log)
        {
            if (y - m_scroll_pos > 0)
                tcod::print(con, {2, y - m_scroll_pos}, tcod::stringf("%s: %u", pair.first.c_str(), pair.second), colors::white, std::nullopt);
            y++;
        }

        tcod::blit(
            m_console,
            con,
            {
                static_cast<int>(m_width) / 2 - UI_WIDTH  / 2,
                static_cast<int>(m_height) / 2 - UI_HEIGHT / 2
            }
        );

        tcod::print(m_console, {static_cast<int>(m_width) - 23, 0}, "Press ESCAPE to restart", colors::white, std::nullopt);
    }
}

void Engine::handle_events()
{
    m_lastkey = SDLK_UNKNOWN;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                m_running = false;
                break;

            case SDL_KEYDOWN:
                m_lastkey = event.key.keysym.sym;
                break;

            case SDL_MOUSEMOTION:
                m_context.convert_event_coordinates(event);
                m_mouse.cx = event.motion.x;
                m_mouse.cy = event.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    m_mouse.lbutton_pressed = true;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    m_mouse.rbutton_pressed = true;
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    m_mouse.lbutton_pressed = false;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    m_mouse.rbutton_pressed = false;
                break;

            default:
                break;
        }
    }
}

void Engine::log(const std::string& name)
{
    if (m_log.find(name) == m_log.end())
        m_log[name] = 1;
    else
        m_log[name]++;
}

void Engine::export_log()
{
#ifdef PATARO_GATHER_ANON_STATS
    std::ofstream f("game-log.csv");
    f << "field,occurences\n";

    for (const auto& pair : m_log)
        f << pair.first << "," << pair.second << "\n";

    f.close();
#endif
}

bool Engine::pick_a_tile(int* x, int* y, float max_range)
{
    int xp = m_player->get_x(),
        yp = m_player->get_y();

    int dx = xp - m_width  / 2,
        dy = yp - m_height / 2;

    while (m_running)
    {
        render();
        handle_events();

        for (int cx = 0, w = m_map->current_level().width(); cx < w; ++cx)
        {
            for (int cy = 0, h = m_map->current_level().height(); cy < h; ++cy)
            {
                float dist = static_cast<float>(details::get_manhattan_distance(cx, cy, xp, yp));

                if (m_map->is_in_fov(cx, cy) && (max_range == 0.f || dist <= max_range))
                {
                    TCOD_ConsoleTile tile = m_console.at(cx - dx, cy - dy);
                    tcod::ColorRGB col = {
                        static_cast<uint8_t>(tile.bg.r * 1.2f),
                        static_cast<uint8_t>(tile.bg.g * 1.2f),
                        static_cast<uint8_t>(tile.bg.b * 1.2f)
                    };
                    m_console.at(cx - dx, cy - dy).bg = col;
                }
            }
        }

        float dist = static_cast<float>(details::get_manhattan_distance(m_mouse.cx + dx, m_mouse.cy + dy, xp, yp));
        if (m_map->is_in_fov(m_mouse.cx + dx, m_mouse.cy + dy) && (max_range == 0.f || dist <= max_range))
        {
            m_console.at(m_mouse.cx, m_mouse.cy).bg = colors::white;

            if (m_mouse.lbutton_pressed)
            {
                *x = m_mouse.cx + dx;
                *y = m_mouse.cy + dy;
                return true;
            }
        }

        if (m_mouse.rbutton_pressed)
            return false;

        flush();
    }

    return false;
}