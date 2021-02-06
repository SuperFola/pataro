#include <Pataro/Actor/Destructible/Player.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Map.hpp>

using namespace pat::actor::details;

PlayerDestructible::PlayerDestructible(float max_hp, float defense, const std::string& corpse_name) :
    Destructible(max_hp, defense, corpse_name)
{}

void PlayerDestructible::die(pat::Actor* owner, pat::Map* map)
{
    std::cout << owner->get_name() << " is dead\n";
    Destructible::die(owner, map);
}
