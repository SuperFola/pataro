#include <Pataro/Engine.hpp>

#include <Pataro/Map/Room.hpp>
#include <Pataro/Utils.hpp>
#include <Pataro/Constants.hpp>

#include <libtcod.hpp>

#include <string>

using namespace pat;

Engine::Engine(unsigned width, unsigned height, const std::string& title)
{
    TCODConsole::initRoot(width, height, title.c_str(), false);
    TCODSystem::setFps(30);

    // instantiate a map with 1 level(s)
    m_map = std::make_unique<Map>(1);

    // create the player
    m_player = std::make_shared<Actor>(
        0, 0, '@', "Player", TCODColor::white
    );
    m_map->current_level().enter(m_player);
}

void Engine::update()
{
    if (m_state == GameState::StartUp)
        m_map->compute_fov(m_player->get_x(), m_player->get_y(), details::player_fov);
    m_state = GameState::Idle;

    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &m_lastkey, nullptr);

    switch (m_lastkey.vk)
    {
        case TCODK_F3:
            TCODSystem::saveScreenshot(("screenshot_" + details::date_to_string() + ".png").c_str());
            break;

        default:
            break;
    }

    // if it's a new turn, update all the actors
    if (m_state == GameState::NewTurn)
        m_map->update(this);
}

void Engine::render()
{
    TCODConsole::root->clear();

    m_map->render();

    TCODConsole::flush();
}

bool Engine::is_running() const
{
    return !TCODConsole::isWindowClosed();
}