#include <Pataro/Actions/LightningBolt.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Animations/Factory.hpp>

using namespace pat::action;

LightningBoltAction::LightningBoltAction(pat::Entity* source, pat::Entity* owner, float range, float damage) :
    m_source(source), m_owner(owner), m_range(range), m_damage(damage)
{}

pat::ActionResult LightningBoltAction::perform(pat::Engine* engine)
{
    if (m_owner == engine->get_player())
        engine->log("lightning bolt");

    pat::Entity* closest = engine->get_map()->get_closest_monster(m_owner, m_range);
    if (closest == nullptr)
    {
        engine->get_gui()->message(TCODColor::lightGrey, "No enemy is close enough to strike.");
        if (m_owner == engine->get_player())
            engine->log("lightning bolt fail");
        return pat::ActionResult::Fail;
    }

    engine->get_gui()->message(TCODColor::lightBlue, "A lightning bolt strikes the ", closest->get_name(), " with a loud thunder!\nThe damage is ", m_damage, " hit points.");
    if (m_owner == engine->get_player())
        engine->log((closest->destructible()->hp() - m_damage <= 0.f ? "lightning bolt kill " : "lightning bolt hit ") + closest->get_name());

    closest->destructible()->take_damage(closest, m_damage, engine);
    // destroy the object, we used it
    m_source->use()->remove_from_container(m_owner, m_source);
    // add an animation
    closest->set_animation(
        animation::Factory::lightningBolt(closest)
    );

    return pat::ActionResult::Success;
}