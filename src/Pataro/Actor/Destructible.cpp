#include <Pataro/Actor/Destructible.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Map.hpp>

#include <libtcod.hpp>

using namespace pat::actor;

Destructible::Destructible(float max_hp, float defense, const std::string& corpse_name) :
    m_max_hp(max_hp), m_hp(max_hp), m_defense(defense), m_corpse_name(corpse_name)
{}

float Destructible::take_damage(pat::Actor* owner, float damage, pat::Map* map)
{
    damage -= m_defense;
    if (damage > 0.f)
    {
        m_hp -= damage;
        if (is_dead())
            die(owner);
    }
    else
        damage = 0.f;

    return damage;
}

void Destructible::die(pat::Actor* owner, pat::Map* map)
{
    owner->morph_into('%', m_corpse_name, TCODColor::darkRed);
    owner->set_blocking(false);
    map->current_level().send_to_back(owner);
}
