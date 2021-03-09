#include <Pataro/Components/Destructible.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

#include <libtcod.hpp>

using namespace pat::component;

Destructible::Destructible(float max_hp, float defense, const std::string& corpse_name) :
    m_max_hp(max_hp), m_hp(max_hp), m_defense(defense), m_corpse_name(corpse_name)
{}

float Destructible::take_damage(pat::Entity* owner, float damage, pat::Engine* engine)
{
    damage -= m_defense;
    if (damage > 0.f)
    {
        m_hp -= damage;
        if (is_dead())
            die(owner, engine);
    }
    else
        damage = 0.f;

    return damage;
}

void Destructible::die(pat::Entity* owner, [[maybe_unused]] pat::Engine* engine)
{
    owner->morph_into('%', TCODColor::darkRed);
    owner->set_name(m_corpse_name);
    owner->set_blocking(false);
}

float Destructible::heal(float amount)
{
    m_hp += amount;
    if (m_hp > m_max_hp)
    {
        amount -= m_hp - m_max_hp;
        m_hp = m_max_hp;
    }
    return amount;
}

Destructible* Destructible::clone_impl() const
{
    return new Destructible(*this);
}