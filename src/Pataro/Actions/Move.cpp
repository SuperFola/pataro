#include <Pataro/Actions/Move.hpp>

#include <Pataro/Constants.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Map/Tile.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Actions/Attack.hpp>

#include <libtcod.hpp>

using namespace pat;

MoveAction::MoveAction(pat::Entity* source, int dx, int dy) :
    m_source(source), m_dx(dx), m_dy(dy)
{}

pat::ActionResult MoveAction::perform(pat::Engine* engine)
{
    int x = m_source->get_x(),
        y = m_source->get_y();

    // if we've found a possible ennemy, attack it
    if (Entity* e = engine->get_map()->get_entity(x + m_dx, y + m_dy); e != nullptr &&
        // so that our player can attack, and monsters will only attack them
        (m_source == engine->get_player() || e == engine->get_player()) &&
        // so that we attack non-dead entities only
        (e->destructible() != nullptr && !e->destructible()->is_dead()))
    {
        return alternate<AttackAction>(engine, m_source, e);
    }

    // physics
    if (!engine->get_map()->can_walk(x + m_dx, y + m_dy))
        return pat::ActionResult::Fail;

    // update player field of view
    // list everything under the player
    if (m_source == engine->get_player())
    {
        // stairs, changing the current level we're on
        // TODO if (engine->get_map()->tile_at(x + m_dx, y + m_dy) == Tile::Type::Stairs)
        //     return alternate<T>(engine, m_source);

        engine->get_map()->compute_fov(x + m_dx, y + m_dy, pat::details::player_fov);
        engine->log("move");

        // if there is something below the player, add a message about it
        if (pat::Entity* e = engine->get_map()->get_entity(x + m_dx, y + m_dy); e != nullptr)
        {
            pat::component::Destructible* d = e->destructible();
            if ((d != nullptr && d->is_dead()) || e->use() != nullptr)
                engine->get_gui()->message(colors::lightGrey, "There is a ", e->get_name(), " here");
        }
    }

    m_source->move(m_dx, m_dy);
    return pat::ActionResult::Success;
}