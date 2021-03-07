#include <Pataro/Actions/Heal.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat::action;

HealAction::HealAction(pat::Entity* source, float quantity) :
    m_source(source), m_quantity(quantity)
{}

pat::ActionResult HealAction::perform([[maybe_unused]] pat::Engine* engine)
{
    if (pat::component::Destructible* d = m_source->destructible(); d != nullptr)
    {
        d->heal(m_quantity);
        return pat::ActionResult::Success;
    }
    return pat::ActionResult::Fail;
}