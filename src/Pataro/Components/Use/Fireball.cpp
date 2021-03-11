#include <Pataro/Components/Use/Fireball.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Actions/Fireball.hpp>

using namespace pat::component::details;

FireballUse::FireballUse(float range, float damage) :
    m_range(range), m_damage(damage)
{}

std::unique_ptr<pat::Action> FireballUse::use(pat::Entity* source, pat::Entity* owner, pat::Engine* engine)
{
    engine->get_gui()->message(TCODColor::cyan, "Left-click a target tile for the fireball,\nor right-click to cancel.");
    int x, y;
    if (!engine->pick_a_tile(&x, &y, m_range))
        return nullptr;

    return std::make_unique<pat::action::FireballAction>(
        source,
        owner,
        x, y,
        m_range,
        m_damage
    );
}

FireballUse* FireballUse::clone_impl() const
{
    return new FireballUse(*this);
}