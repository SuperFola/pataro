#include <Pataro/Actions/Attack.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat;

AttackAction::AttackAction(pat::Entity* source, pat::Entity* target) :
    m_source(source), m_target(target)
{}

pat::ActionResult AttackAction::perform(pat::Engine* engine)
{
    if (pat::component::Attacker* a = m_source->attacker(); a != nullptr)
    {
        if (m_source == engine->get_player())
            engine->log("attack");

        // attack only if the other can be attacked
        if (pat::component::Destructible* d = m_target->destructible(); d != nullptr)
        {
            TCODColor text_color = (m_source == engine->get_player()) ? TCODColor::red : TCODColor::lightGrey;
            float dmg = a->power() - d->defense();
            if (dmg > 0.f)
                engine->get_gui()->message(text_color, m_source->get_name(), " attacks ", m_target->get_name(), " for ", dmg, " hit points.");
            else
                engine->get_gui()->message(TCODColor::lightGrey, m_source->get_name(), " attacks ", m_target->get_name(), " but it has no effect!");

            if (m_source == engine->get_player())
                engine->log((d->hp() - dmg <= 0.f ? "kill " : "hit ") + m_target->get_name());
            else if (m_target == engine->get_player())
                engine->log(m_source->get_name() + (d->hp() - dmg <= 0.f ? " kill player" : " hit player"));

            d->take_damage(m_target, a->power(), engine);
            return pat::ActionResult::Success;
        }

        if (m_source == engine->get_player())
            engine->log("vain attack");

        engine->get_gui()->message(TCODColor::lightGrey, m_source->get_name(), " attacks ", m_target->get_name(), " in vain");
        return pat::ActionResult::Fail;
    }

    return pat::ActionResult::Fail;
}