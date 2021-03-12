#include <Pataro/Actions/Fireball.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Animations/Factory.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Utils.hpp>

using namespace pat::action;

FireballAction::FireballAction(pat::Entity* source, pat::Entity* owner, int tx, int ty, float range, float damage) :
    m_source(source), m_owner(owner), m_tx(tx), m_ty(ty), m_range(range), m_damage(damage)
{}

pat::ActionResult FireballAction::perform(pat::Engine* engine)
{
    engine->get_gui()->message(TCODColor::orange, "The fireball explodes, burning everything within ", m_range, " tiles!");
    if (m_owner == engine->get_player())
        engine->log("fireball");

    for (const auto& entity: engine->get_map()->current_level().get_entities())
    {
        float dist = static_cast<float>(details::get_manhattan_distance(entity->get_x(), entity->get_y(), m_tx, m_ty));
        if (pat::component::Destructible* d = entity->destructible(); d != nullptr && !d->is_dead() && dist < m_range)
        {
            engine->get_gui()->message(TCODColor::orange, "The ", entity->get_name(), " gets burned for ", m_damage, " hit points.");
            if (m_owner == engine->get_player())
                engine->log((d->hp() - m_damage <= 0.f ? "fireball kill " : "fireball hit ") + entity->get_name());

            d->take_damage(entity.get(), m_damage, engine);
            // add an animation
            entity->set_animation(
                animation::Factory::burning(entity.get())
            );
        }
    }

    // destroy the object, we used it
    m_source->use()->remove_from_container(m_owner, m_source);

    return pat::ActionResult::Success;
}