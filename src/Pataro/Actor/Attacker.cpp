#include <Pataro/Actor/Attacker.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Actor/Destructible.hpp>

#include <iostream>

using namespace pat::actor;

Attacker::Attacker(float power) :
    m_power(power)
{}

void Attacker::attack(pat::Actor* owner, pat::Actor* target, pat::Engine* engine)
{
    if (Destructible* d = target->destructible(); d != nullptr)
    {
        TCODColor text_color = (owner == engine->get_player()) ? TCODColor::red : TCODColor::lightGrey;
        if (float dmg = d->take_damage(target, m_power, engine); dmg > 0.f)
            engine->get_gui()->message(text_color, owner->get_name(), " attacks ", target->get_name(), " for ", dmg, " hit points.");
        else
            engine->get_gui()->message(TCODColor::lightGrey, owner->get_name(), " attacks ", target->get_name(), " but it has no effect!");
    }
    else
        engine->get_gui()->message(TCODColor::lightGrey, owner->get_name(), " attacks ", target->get_name(), " in vain");
}