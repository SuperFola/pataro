#include <Pataro/Actions/Drop.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>

using namespace pat;

DropAction::DropAction(pat::Entity* owner, pat::Entity* object) :
    m_owner(owner), m_object(object)
{}

pat::ActionResult DropAction::perform(pat::Engine* engine)
{
    if (m_owner == engine->get_player())
        engine->log("drop " + m_object->get_name());

    m_object->use()->drop(m_object, m_owner, engine);
    engine->get_gui()->message(colors::lightGrey, m_owner->get_name(), " drops a ", m_object->get_name(), ".");

    return pat::ActionResult::Success;
}