#include <Pataro/Actions/PickUp.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Use.hpp>

using namespace pat::action;

PickUpAction::PickUpAction(pat::Entity* source, int x, int y) :
    m_source(source), m_x(x), m_y(y)
{}

// FIXME it will only work for the player (in the GUI, using pronoun 'you')
pat::ActionResult PickUpAction::perform(pat::Engine* engine)
{
    bool found = false;

    for (const auto& e : engine->get_map()->current_level().get_entities())
    {
        if (component::Use* u = e->use(); u != nullptr && e->get_x() == m_x && e->get_y() == m_y)
        {
            // try to pick up the object
            if (m_source->container()->add(e.get()))
            {
                found = true;
                engine->get_gui()->message(TCODColor::lightGrey, "You pick up the ", e->get_name());
                engine->get_map()->current_level().remove(e.get());
                return pat::ActionResult::Success;
            }
            else if (!found)
            {
                // we found an object but couldn't pick it up
                found = true;
                engine->get_gui()->message(TCODColor::red, "Your inventory is full.");
                return pat::ActionResult::Fail;
            }
        }
    }

    engine->get_gui()->message(TCODColor::lightGrey, "There's nothing here that you can pick up");
    return pat::ActionResult::Fail;
}