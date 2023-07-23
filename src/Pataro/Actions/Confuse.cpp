#include <Pataro/Actions/Confuse.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Components/AI/ConfusedMonster.hpp>
#include <Pataro/Components/Use/OneTimeSelect.hpp>
#include <Pataro/Utils.hpp>

using namespace pat;

ConfuseAction::ConfuseAction(pat::Entity* source, pat::Entity* owner, const pat::component::PickTile* picker, int nb_turns) :
    m_source(source), m_owner(owner), m_target(picker->get_entity()), m_nb_turns(nb_turns)
{}

pat::ActionResult ConfuseAction::perform(pat::Engine* engine)
{
    engine->get_gui()->message(colors::lightGreen, "The eyes of the ", m_target->get_name(), " look vacant\nas they starts to stumble around!");
    if (m_owner == engine->get_player())
        engine->log("confuse " + m_target->get_name());

    // change the monster AI to a confused one
    m_target->set_ai<component::ConfusedMonsterAI>(m_nb_turns, std::move(m_target->move_ai()));
    // destroy the object, we used it
    m_source->use()->remove_from_inventory(m_owner, m_source);

    return pat::ActionResult::Success;
}