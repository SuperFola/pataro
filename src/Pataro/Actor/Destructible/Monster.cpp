#include <Pataro/Actor/Destructible/Monster.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Map.hpp>

#include <iostream>

using namespace pat::actor::details;

MonsterDestructible::MonsterDestructible(float max_hp, float defense, const std::string& corpse_name) :
    Destructible(max_hp, defense, corpse_name)
{}

void MonsterDestructible::die(pat::Actor* owner, pat::Map* map)
{
    std::cout << owner->get_name() << " is dead\n";
    Destructible::die(owner, map);
}
