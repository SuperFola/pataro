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
        return std::make_unique<pat::action::MoveAction>(owner, dx, dy);
    }

    return nullptr;
}

PlayerAI* PlayerAI::clone_impl() const
{
    return new PlayerAI(*this);
}