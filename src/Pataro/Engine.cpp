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

#include <libtcod.hpp>

#include <utility>
#include <fstream>

using namespace pat;

Engine::Engine(unsigned width, unsigned height, const std::string& title, bool show_debug) :
    m_width(width), m_height(height), m_show_debug(show_debug)
{
    TCODConsole::initRoot(width, height, title.c_str(), false);
    TCODSystem::setFps(30);

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

    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &m_lastkey, &m_mouse);

    // player actions only activated if we haven't lost
    if (m_state != GameState::Defeat)
    {
        std::unique_ptr<Action> action = m_player->update(this);
        if (action)
            action->perform(this);
    }

    switch (m_lastkey.vk)
    {
        case TCODK_F3:
            TCODSystem::saveScreenshot(("screenshot_" + details::date_to_string() + ".png").c_str());
            break;

        case TCODK_UP:
        case TCODK_LEFT:
            if (m_state == GameState::Defeat)
                m_scroll_pos = m_scroll_pos <= 0 ? 0 : m_scroll_pos - 1;
            break;

        case TCODK_DOWN:
        case TCODK_RIGHT:
            if (m_state == GameState::Defeat)
                m_scroll_pos = m_scroll_pos + 1 >= static_cast<int>(m_log.size()) ? static_cast<int>(m_log.size()) - 1 : m_scroll_pos + 1;
            break;

        case TCODK_ESCAPE:
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
    TCODConsole::root->clear();

    m_map->render(this);
    m_gui->render(this, TCODConsole::root, 0, m_height - m_gui->get_height());

    if (m_show_debug)
    {
        TCODConsole::root->setDefaultForeground(colors::white);
        TCODConsole::root->printf(0, 0, "%.2f", 1.f / TCODSystem::getLastFrameLength());
    }

    // defeat ui
    if (m_state == GameState::Defeat)
    {
        static const int UI_WIDTH = 50, UI_HEIGHT = 28;
        static TCODConsole con(UI_WIDTH, UI_HEIGHT);

        con.setDefaultForeground(tcod::ColorRGB(50, 180, 200));
        con.printFrame(0, 0, UI_WIDTH, UI_HEIGHT, true, TCOD_BKGND_DEFAULT, "Game statistics");

        // display the items with their keyboard shortcut
        con.setDefaultForeground(colors::white);
        int y = 1;

        for (const auto& pair : m_log)
        {
            if (y - m_scroll_pos > 0)
                con.printf(2, y - m_scroll_pos, "%s: %u", pair.first.c_str(), pair.second);
            y++;
        }

        TCODConsole::blit(
            &con, 0, 0, UI_WIDTH, UI_HEIGHT,
            TCODConsole::root,
            m_width  / 2 - UI_WIDTH  / 2,
            m_height / 2 - UI_HEIGHT / 2
        );

        TCODConsole::root->setDefaultForeground(colors::white);
        TCODConsole::root->printf(m_width - 23, 0, "Press ESCAPE to restart");
    }
}

bool Engine::is_running() const
{
    return !TCODConsole::isWindowClosed();
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

    while (is_running())
    {
        render();

        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &m_lastkey, &m_mouse);

        for (int cx = 0, w = m_map->current_level().width(); cx < w; ++cx)
        {
            for (int cy = 0, h = m_map->current_level().height(); cy < h; ++cy)
            {
                float dist = static_cast<float>(details::get_manhattan_distance(cx, cy, xp, yp));

                if (m_map->is_in_fov(cx, cy) && (max_range == 0.f || dist <= max_range))
                {
                    TCODColor col = TCODConsole::root->getCharBackground(cx - dx, cy - dy);
                    col = col * 1.2f;
                    TCODConsole::root->setCharBackground(cx - dx, cy - dy, col);
                }
            }
        }

        float dist = static_cast<float>(details::get_manhattan_distance(m_mouse.cx + dx, m_mouse.cy + dy, xp, yp));
        if (m_map->is_in_fov(m_mouse.cx + dx, m_mouse.cy + dy) && (max_range == 0.f || dist <= max_range))
        {
            TCODConsole::root->setCharBackground(m_mouse.cx, m_mouse.cy, colors::white);

            if (m_mouse.lbutton_pressed)
            {
                *x = m_mouse.cx + dx;
                *y = m_mouse.cy + dy;
                return true;
            }
        }

        if (m_mouse.rbutton_pressed)
            return false;

        TCODConsole::flush();
    }

    return false;
}