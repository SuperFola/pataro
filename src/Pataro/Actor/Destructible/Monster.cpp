#include <Pataro/Actor/Destructible/Monster.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Engine.hpp>

#include <iostream>

using namespace pat::actor::details;

MonsterDestructible::MonsterDestructible(float max_hp, float defense, const std::string& corpse_name) :
    Destructible(max_hp, defense, corpse_name)
{}

void MonsterDestructible::die(pat::Actor* owner, pat::Engine* engine)
{
    engine->get_gui()->message(TCODColor::lightGrey, owner->get_name(), " is dead");
    Destructible::die(owner, engine);
}
