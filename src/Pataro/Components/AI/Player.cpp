#include <Pataro/Components/AI/Player.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Constants.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Components/Inventory.hpp>

#include <Pataro/Actions/Move.hpp>
#include <Pataro/Actions/Attack.hpp>
#include <Pataro/Actions/PickUp.hpp>
#include <Pataro/Actions/Use.hpp>
#include <Pataro/Actions/Drop.hpp>

#include <SDL2/SDL_keycode.h>

using namespace pat::component;

std::unique_ptr<pat::Action> PlayerAI::update(pat::Entity* owner, pat::Engine* engine)
{
    // do nothing if we're dead
    if (Destructible* d = owner->destructible(); d != nullptr && d->is_dead())
    {
        engine->change_state(pat::GameState::Defeat);
        return nullptr;
    }

    int dx = 0,
        dy = 0;
    std::unique_ptr<pat::Action> action;

    switch (engine->lastkey())
    {
        case SDLK_UP:    --dy; break;
        case SDLK_DOWN:  ++dy; break;
        case SDLK_LEFT:  --dx; break;
        case SDLK_RIGHT: ++dx; break;

        default:
            action = handle_action_key(owner, engine, engine->lastkey());
            break;
    }

    if (dy != 0 || dx != 0)
    {
        engine->change_state(pat::GameState::NewTurn);
        engine->log("turn");
        return std::make_unique<pat::MoveAction>(owner, dx, dy);
    }
    else if (action)
    {
        engine->change_state(pat::GameState::NewTurn);
        engine->log("turn");
        return action;
    }

    return nullptr;
}

std::unique_ptr<pat::Action> PlayerAI::handle_action_key(pat::Entity* owner, pat::Engine* engine, int keycode)
{
    // TODO find a way to make the keycode customisable
    switch (keycode)
    {
        // pick an item
        case SDLK_g:
            return std::make_unique<pat::PickUpAction>(owner, owner->get_x(), owner->get_y());

        // display inventory
        case SDLK_i:
        {
            Entity* e = engine->choose_from_inventory(owner);
            if (e != nullptr)
                return std::make_unique<pat::UseAction>(owner, e);
            break;
        }

        // drop an object
        case SDLK_d:
        {
            Entity* e = engine->choose_from_inventory(owner);
            if (e != nullptr)
                return std::make_unique<pat::DropAction>(owner, e);
            break;
        }

        default:
            break;
    }

    return nullptr;
}

PlayerAI* PlayerAI::clone_impl() const
{
    return new PlayerAI(*this);
}