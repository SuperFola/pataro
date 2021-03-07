#include <Pataro/Actions/Heal.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat::action;

HealAction::HealAction(pat::Entity* source, float quantity) :
    m_source(source), m_quantity(quantity)
{}

pat::ActionResult HealAction::perform(pat::Engine* engine)
{
    if (pat::component::Destructible* d = m_source->destructible(); d != nullptr)
    {
        float healed = d->heal(m_quantity);
        engine->get_gui()->message(TCODColor::lightGreen, m_source->get_name(), " healed ", healed, "HP");

        return pat::ActionResult::Success;
    }
    return pat::ActionResult::Fail;
}