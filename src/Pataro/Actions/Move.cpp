#include <Pataro/Actions/Move.hpp>

#include <Pataro/Constants.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Map/Tile.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Actions/Attack.hpp>
#include <Pataro/Actions/FollowStairs.hpp>

using namespace pat;

MoveAction::MoveAction(Entity* source, int dx, int dy) :
    m_source(source), m_dx(dx), m_dy(dy)
{}

ActionResult MoveAction::perform(Engine* engine)
{
    int x = m_source->get_x(),
        y = m_source->get_y();
    Entity* player = engine->get_player();
    Map* map = engine->get_map();

    // if we've found a possible ennemy, attack it
    if (Entity* e = map->get_entity(x + m_dx, y + m_dy); e != nullptr &&
        // so that our player can attack, and monsters will only attack them
        (m_source == player || e == player) &&
        // so that we attack non-dead entities only
        (e->destructible() != nullptr && !e->destructible()->is_dead()))
    {
        return alternate<AttackAction>(engine, m_source, e);
    }

    // physics
    // TODO probably going to have to refactor either this, the way we handle the map (tiles+tcod map?) or both
    map::Tile::Type next_tile = map->tile_at(x + m_dx, y + m_dy);
    if (!map->can_walk(x + m_dx, y + m_dy))
        return ActionResult::Fail;

    // update player field of view
    // list everything under the player
    if (m_source == player)
    {
        // stairs, changing the current level we're on
        // FIXME: find a way to encode stairs going up and stairs going down
        if (next_tile == map::Tile::Type::Stairs)
            return alternate<FollowStairsAction>(engine, m_source, FollowStairsAction::Direction::Down);

        map->compute_fov(x + m_dx, y + m_dy, details::player_fov);
        engine->log("move");

        // if there is something below the player, add a message about it
        if (Entity* e = map->get_entity(x + m_dx, y + m_dy); e != nullptr)
        {
            component::Destructible* d = e->destructible();
            if ((d != nullptr && d->is_dead()) || e->use() != nullptr)
                engine->get_gui()->message(colors::lightGrey, "There is a ", e->get_name(), " here");
        }
    }

    m_source->move(m_dx, m_dy);
    return ActionResult::Success;
}