#include <Pataro/Engine.hpp>
#include <Pataro/Map/Room.hpp>
#include <Pataro/Utils.hpp>

#include <libtcod.hpp>

#include <string>

using namespace pat;

Engine::Engine(unsigned width, unsigned height, const std::string& title)
{
    TCODConsole::initRoot(width, height, title.c_str(), false);
    TCODSystem::setFps(30);

    // instantiate a map with 1 level(s)
    m_map = std::make_unique<Map>(1);
    const map::details::Room& first_room = m_map->current_level().get_first_room();

    // create the player at the center of the first room
    m_player = m_map->current_level().create_player('@', "Player", TCODColor::white);
}

void Engine::update()
{
    if (m_state == GameStatus::StartUp)
        m_map->compute_fov(m_player->get_x(), m_player->get_y(), m_fov_radius);
    m_state = GameStatus::Idle;

    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr);

    int dx = 0,
        dy = 0;

    switch (key.vk)
    {
        case TCODK_UP:    --dy; break;
        case TCODK_DOWN:  ++dy; break;
        case TCODK_LEFT:  --dx; break;
        case TCODK_RIGHT: ++dx; break;

        case TCODK_F3:
            TCODSystem::saveScreenshot(("screenshot_" + details::date_to_string() + ".png").c_str());
            break;

        default:
            break;
    }

    if (dy != 0 || dx != 0)
    {
        m_state = GameStatus::NewTurn;

        if (player->move_or_attack(dx, dy, m_map.get()))
            m_map->compute_fov(m_player->get_x(), m_player->get_y(), m_fov_radius);
    }
}

void Engine::render()
{
    TCODConsole::root->clear();

    m_map->render();
    m_player->render();

    TCODConsole::flush();
}

bool Engine::is_running() const
{
    return !TCODConsole::isWindowClosed();
}