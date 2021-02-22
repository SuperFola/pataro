#include <Pataro/Components/AI/Player.hpp>

#include <Pataro/Constants.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat::component::details;

void PlayerAI::update(pat::Entity* owner, pat::Engine* engine)
{
    // do nothing if we're dead
    if (Destructible* d = owner->destructible(); d != nullptr && d->is_dead())
        return;

    int dx = 0,
        dy = 0;

    switch (engine->lastkey().vk)
    {
        case TCODK_UP:    --dy; break;
        case TCODK_DOWN:  ++dy; break;
        case TCODK_LEFT:  --dx; break;
        case TCODK_RIGHT: ++dx; break;
        // TODO handle other keys
        default:                break;
    }

    // if we were able to move, compute a new game state and field of view
    if (dy != 0 || dx != 0)
    {
        engine->change_state(pat::GameState::NewTurn);

        if (move_or_attack(owner, dx, dy, engine))
            engine->get_map()->compute_fov(owner->get_x(), owner->get_y(), pat::details::player_fov);
    }
}

bool PlayerAI::move_or_attack(pat::Entity* owner, int dx, int dy, pat::Engine* engine)
{
    int x = owner->get_x(),
        y = owner->get_y();

    if (engine->get_map()->is_wall(x + dx, y + dy))
        return false;

    if (Entity* a = engine->get_map()->get_entity(x + dx, y + dy); a != nullptr)
    {
        Destructible* d = a->destructible();

        // found a possible ennemy, attack it
        if (d != nullptr && !d->is_dead())
        {
            owner->attacker()->attack(owner, a, engine);
            return false;
        }
        else if (d != nullptr && d->is_dead())
            engine->get_gui()->message(TCODColor::lightGrey, "There is a ", a->get_name(), " here");
    }

    owner->put_at(x + dx, y + dy);
    return true;
}
