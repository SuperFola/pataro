#include <Pataro/Actions/Use.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>

using namespace pat::action;

UseAction::UseAction(pat::Entity* owner, pat::Entity* object) :
    m_owner(owner), m_object(object)
{}

pat::ActionResult UseAction::perform(pat::Engine* engine)
{
    // perform the action of the object itself
    std::unique_ptr<Action> action = m_object->use()->perform(m_object, m_owner, engine);
    if (action != nullptr)
        return action->perform(engine);
    return pat::ActionResult::Fail;
}