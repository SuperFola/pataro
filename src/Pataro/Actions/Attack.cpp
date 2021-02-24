#include <Pataro/Actions/Attack.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Attacker.hpp>

using namespace pat::action;

AttackAction::AttackAction(pat::Entity* source, pat::Entity* target) :
    m_source(source), m_target(target)
{}

pat::ActionResult AttackAction::perform(pat::Engine* engine)
{
    if (pat::component::Attacker* a = m_source->attacker(); a != nullptr)
    {
        // FIXME there is code in there which should be here
        a->attack(m_source, m_target, engine);
        return pat::ActionResult::Success;
    }

    return pat::ActionResult::Fail;
}