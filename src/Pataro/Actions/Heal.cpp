#include <Pataro/Actions/Heal.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat::action;

HealAction::HealAction(pat::Entity* source, pat::Entity* owner, float quantity) :
    m_source(source), m_owner(owner), m_quantity(quantity)
{}

pat::ActionResult HealAction::perform(pat::Engine* engine)
{
    if (pat::component::Destructible* d = m_owner->destructible(); d != nullptr)
    {
        float healed = d->heal(m_quantity);
        engine->get_gui()->message(TCODColor::lightGreen, m_owner->get_name(), " healed ", healed, "HP");

        if (healed > 0.f)
            m_source->use()->mark_destroyed();

        return pat::ActionResult::Success;
    }
    return pat::ActionResult::Fail;
}