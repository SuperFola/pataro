#include <Pataro/Actor/Attacker.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Map.hpp>
#include <Pataro/Actor/Destructible.hpp>

#include <iostream>

using namespace pat::actor;

Attacker::Attacker(float power) :
    m_power(power)
{}

void Attacker::attack(pat::Actor* owner, pat::Actor* target, pat::Map* map)
{
    if (Destructible* d = target->destructible(); d != nullptr)
    {
        if (float dmg = d->take_damage(target, m_power, map); dmg > 0.f)
            std::cout << owner->get_name() << " attacks " << target->get_name() << " for " << dmg << " hit points.\n";
        else
            std::cout << owner->get_name() << " attacks " << target->get_name() << " but it has no effect!\n";
    }
    else
        std::cout << owner->get_name() << " attacks " << target->get_name() << " in vain\n";
}