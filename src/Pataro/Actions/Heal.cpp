#include <Pataro/Actions/Heal.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat;

HealAction::HealAction(pat::Entity* source, pat::Entity* owner, float quantity) :
    m_source(source), m_owner(owner), m_quantity(quantity)
{}

pat::ActionResult HealAction::perform(pat::Engine* engine)
{
    if (pat::component::Destructible* d = m_owner->destructible(); d != nullptr)
    {
        float healed = d->heal(m_quantity);
        engine->get_gui()->message(colors::lightGreen, m_owner->get_name(), " healed ", healed, "HP");
        if (m_owner == engine->get_player())
            engine->log("heal");

        if (healed > 0.f)
            m_source->use()->remove_from_container(m_owner, m_source);

        return pat::ActionResult::Success;
    }
    return pat::ActionResult::Fail;
}