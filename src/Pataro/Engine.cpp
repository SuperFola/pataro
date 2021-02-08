#include <Pataro/Engine.hpp>

#include <Pataro/Map/Room.hpp>
#include <Pataro/Utils.hpp>
#include <Pataro/Constants.hpp>
#include <Pataro/Map/Constants.hpp>
#include <Pataro/Actor/AI/Player.hpp>
#include <Pataro/Actor/Attacker.hpp>
#include <Pataro/Actor/Destructible/Player.hpp>

#include <libtcod.hpp>

#include <string>
#include <utility>

using namespace pat;

Engine::Engine(unsigned width, unsigned height, const std::string& title) :
    m_width(width), m_height(height)
{
    TCODConsole::initRoot(width, height, title.c_str(), false);
    TCODSystem::setFps(30);

    // instantiate a map with 1 level(s)
    m_map = std::make_unique<Map>(map::details::level_w, map::details::level_h, 1);

    // create the player
    m_player = std::make_shared<Actor>(0, 0, '@', "Player", TCODColor::white);
    m_player->set_ai<actor::details::PlayerAI>();
    m_player->set_attacker<actor::Attacker>(5.f);
    m_player->set_destructible<actor::details::PlayerDestructible>(30.f, 2.f, "your cadaver");

    m_map->current_level().enter(m_player);

    // setup gui
    Gui::Proxy_t proxy_player_hp = [this](float* val, float* max_val) -> void {
        *val     = m_player->destructible()->hp();
        *max_val = m_player->destructible()->max_hp();
    };
    unsigned gui_height = 7;  // TODO put it elsewhere
    m_gui = std::make_unique<Gui>(m_width, gui_height, proxy_player_hp, TCODConsole::root, Gui::Pos_t{0, m_height - gui_height});
}

void Engine::update()
{
    if (m_state == GameState::StartUp)
        m_map->compute_fov(m_player->get_x(), m_player->get_y(), details::player_fov);
    m_state = GameState::Idle;

    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &m_lastkey, nullptr);
    m_player->update(this);

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
    m_gui->render();

    TCODConsole::flush();
}

bool Engine::is_running() const
{
    return !TCODConsole::isWindowClosed();
}