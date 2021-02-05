#include <Pataro/Engine.hpp>

#include <libtcod.hpp>

using namespace pat;

Engine::Engine(unsigned width, unsigned height, const std::string& title)
{
    TCODConsole::initRoot(width, height, title.c_str(), false);
    TCODSystem::setFps(30);

    // instantiate a map with 1 level(s)
    m_map = std::make_unique<Map>(1);
    // create player
    m_player = std::make_unique<Actor>(40, 25, '@', TCODColor::white);
}

void Engine::update()
{
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr);

    int x = m_player->get_x(),
        y = m_player->get_y();

    switch (key.vk)
    {
        case TCODK_UP:
            m_player->move(0, -1, m_map.get());
            break;

        case TCODK_DOWN:
            m_player->move(0, 1, m_map.get());
            break;

        case TCODK_LEFT:
            m_player->move(-1, 0, m_map.get());
            break;

        case TCODK_RIGHT:
            m_player->move(1, 0, m_map.get());
            break;

        case TCODK_F3:
            // TODO make it better
            TCODSystem::saveScreenshot("screenshot.png");
            break;

        default:
            break;
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