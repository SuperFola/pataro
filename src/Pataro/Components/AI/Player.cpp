#include <Pataro/Components/AI/Player.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Actions/Move.hpp>
#include <Pataro/Actions/Attack.hpp>

using namespace pat::component::details;

std::unique_ptr<pat::Action> PlayerAI::update(pat::Entity* owner, pat::Engine* engine)
{
    // do nothing if we're dead
    if (Destructible* d = owner->destructible(); d != nullptr && d->is_dead())
        return nullptr;

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
        return move_or_attack(owner, dx, dy, engine);
    }

    return nullptr;
}

std::unique_ptr<pat::Action> PlayerAI::move_or_attack(pat::Entity* owner, int dx, int dy, pat::Engine* engine)
{
    int x = owner->get_x(),
        y = owner->get_y();

    // physics
    if (engine->get_map()->is_wall(x + dx, y + dy))
        return nullptr;

    if (Entity* a = engine->get_map()->get_entity(x + dx, y + dy); a != nullptr)
    {
        // found a possible ennemy, attack it
        if (Destructible* d = a->destructible(); d != nullptr && !d->is_dead())
            return std::make_unique<pat::action::AttackAction>(owner, a);
    }

    // move, nothing is preventing us from moving
    return std::make_unique<pat::action::MoveAction>(owner, dx, dy);
}
