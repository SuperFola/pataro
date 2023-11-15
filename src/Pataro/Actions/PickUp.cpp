#include <Pataro/Actions/PickUp.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Components/Use.hpp>

using namespace pat;

PickUpAction::PickUpAction(pat::Entity* source, int x, int y) :
    m_source(source), m_x(x), m_y(y)
{}

pat::ActionResult PickUpAction::perform(pat::Engine* engine)
{
    if (m_source == engine->get_player())
        engine->log("pick up");

    for (const auto& e : engine->get_map()->current_level().get_entities())
    {
        if (component::Use* u = e->use(); u != nullptr && e->get_x() == m_x && e->get_y() == m_y)
        {
            // try to pick up the object
            if (m_source->inventory()->add(e.get()))
            {
                if (m_source == engine->get_player())
                {
                    engine->log("pick up " + e->get_name());
                    engine->get_gui()->message(colors::lightGrey, "You pick up the ", e->get_name());
                }
                else
                    engine->get_gui()->message(colors::lightGrey, m_source->get_name(), " picks up the ", e->get_name());

                engine->get_map()->current_level().remove(e.get());
                return pat::ActionResult::Success;
            }
            else
            {
                // we found an object but couldn't pick it up
                if (m_source == engine->get_player())
                {
                    engine->log("pick up with full inventory");
                    engine->get_gui()->message(colors::red, "Your inventory is full.");
                }
                else
                    engine->get_gui()->message(colors::red, m_source->get_name(), " inventory's is full.");
                return pat::ActionResult::Fail;
            }
        }
    }

    if (m_source == engine->get_player())
    {
        engine->log("pick up impossible");
        engine->get_gui()->message(colors::lightGrey, "There's nothing here that you can pick up");
    }
    return pat::ActionResult::Fail;
}