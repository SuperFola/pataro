#include <Pataro/Engine.hpp>

#include <libtcod.hpp>

using namespace pat;

Engine::Engine(unsigned width, unsigned height, const std::string& title)
{
    TCODConsole::initRoot(width, height, title.c_str(), false);

    m_map = std::make_unique<Map>(5);

    // create player
    m_actors.emplace_back(std::make_unique<Actor>(40, 25, '@', TCODColor::white));
    m_player = m_actors.back().get();

    // TODO clean up
    m_actors.emplace_back(std::make_unique<Actor>(60, 13, '@', TCODColor::yellow));
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

        default:
            break;
    }
}

void Engine::render()
{
    TCODConsole::root->clear();

    m_map->render();
    for (const std::unique_ptr<Actor>& actor : m_actors)
        actor->render();

    TCODConsole::flush();
}

bool Engine::is_running() const
{
    return !TCODConsole::isWindowClosed();
}