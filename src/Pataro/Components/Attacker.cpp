#include <Pataro/Components/Attacker.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat::component;

Attacker::Attacker(float power) :
    m_power(power)
{}

void Attacker::attack(pat::Entity* owner, pat::Entity* target, pat::Engine* engine)
{
    // attack only if the other can be attacked
    if (Destructible* d = target->destructible(); d != nullptr)
    {
        TCODColor text_color = (owner == engine->get_player()) ? TCODColor::red : TCODColor::lightGrey;
        float dmg = m_power - d->defense();
        if (dmg > 0.f)
            engine->get_gui()->message(text_color, owner->get_name(), " attacks ", target->get_name(), " for ", dmg, " hit points.");
        else
            engine->get_gui()->message(TCODColor::lightGrey, owner->get_name(), " attacks ", target->get_name(), " but it has no effect!");
        d->take_damage(target, m_power, engine);
    }
    else
        engine->get_gui()->message(TCODColor::lightGrey, owner->get_name(), " attacks ", target->get_name(), " in vain");
}