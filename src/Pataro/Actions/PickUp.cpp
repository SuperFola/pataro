#include <Pataro/Actions/PickUp.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Use.hpp>

using namespace pat;

PickUpAction::PickUpAction(pat::Entity* source, int x, int y) :
    m_source(source), m_x(x), m_y(y)
{}

pat::ActionResult PickUpAction::perform(pat::Engine* engine)
{
    bool found = false;
    if (m_source == engine->get_player())
        engine->log("pick up");

    for (const auto& e : engine->get_map()->current_level().get_entities())
    {
        if (component::Use* u = e->use(); u != nullptr && e->get_x() == m_x && e->get_y() == m_y)
        {
            // try to pick up the object
            if (m_source->container()->add(e.get()))
            {
                found = true;

                if (m_source == engine->get_player())
                {
                    engine->log("pick up " + e->get_name());
                    engine->get_gui()->message(TCODColor::lightGrey, "You pick up the ", e->get_name());
                }
                else
                    engine->get_gui()->message(TCODColor::lightGrey, m_source->get_name(), " picks up the ", e->get_name());

                engine->get_map()->current_level().remove(e.get());
                return pat::ActionResult::Success;
            }
            else if (!found)
            {
                // we found an object but couldn't pick it up
                found = true;

                if (m_source == engine->get_player())
                {
                    engine->log("pick up with full inventory");
                    engine->get_gui()->message(TCODColor::red, "Your inventory is full.");
                }
                else
                    engine->get_gui()->message(TCODColor::red, m_source->get_name(), " inventory's is full.");
                return pat::ActionResult::Fail;
            }
        }
    }

    if (m_source == engine->get_player())
    {
        engine->log("pick up impossible");
        engine->get_gui()->message(TCODColor::lightGrey, "There's nothing here that you can pick up");
    }
    return pat::ActionResult::Fail;
}