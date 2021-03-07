#include <Pataro/Components/AI/Player.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Components/Use.hpp>
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
    bool action = false;

    switch (engine->lastkey().vk)
    {
        case TCODK_UP:
            --dy;
            action = true;
            break;

        case TCODK_DOWN:
            ++dy;
            action = true;
            break;

        case TCODK_LEFT:
            --dx;
            action = true;
            break;

        case TCODK_RIGHT:
            ++dx;
            action = true;
            break;


        case TCODK_CHAR:
            handle_action_key(owner, engine, engine->lastkey().c);
            action = true;
            break;

        default:
            break;
    }

    if (action)
    {
        engine->change_state(pat::GameState::NewTurn);

        if (dy != 0 || dx != 0)
            return std::make_unique<pat::action::MoveAction>(owner, dx, dy);
    }

    return nullptr;
}

bool PlayerAI::handle_action_key(pat::Entity* owner, pat::Engine* engine, int ascii)
{
    switch (ascii)
    {
        // pick an item
        case 'g':
        {
            bool found = false;
            for (const auto& e : engine->get_map()->current_level().get_entities())
            {
                if (Use* u = e->use(); u != nullptr
                    && e->get_x() == owner->get_x()
                    && e->get_y() == owner->get_y())
                {
                    // try to pick up the object
                    if (owner->container()->add(e.get()))
                    {
                        found = true;
                        engine->get_gui()->message(TCODColor::lightGrey, "You pick up the ", e->get_name());
                    }
                    else if (!found)
                    {
                        // we found an object but couldn't pick it up
                        found = true;
                        engine->get_gui()->message(TCODColor::red, "Your inventory is full.");
                    }
                }

                if (found)
                    break;
            }

            if (!found)
                engine->get_gui()->message(TCODColor::lightGrey, "There's nothing here that you can pick up");
            return true;
        }
    }

    return false;
}

PlayerAI* PlayerAI::clone_impl() const
{
    return new PlayerAI(*this);
}