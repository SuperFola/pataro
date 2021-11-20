#include <Pataro/Actions/Use.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>

using namespace pat;

UseAction::UseAction(pat::Entity* owner, pat::Entity* object) :
    m_owner(owner), m_object(object)
{}

pat::ActionResult UseAction::perform(pat::Engine* engine)
{
    // perform the action of the object itself
    std::unique_ptr<Action> action = m_object->use()->perform(m_object, m_owner, engine);
    if (action != nullptr)
    {
        if (m_owner == engine->get_player())
            engine->log("use " + m_object->get_name());
        return action->perform(engine);
    }
    return pat::ActionResult::Fail;
}