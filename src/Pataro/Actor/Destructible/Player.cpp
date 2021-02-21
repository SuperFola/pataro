#include <Pataro/Actor/Destructible/Player.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::actor::details;

PlayerDestructible::PlayerDestructible(float max_hp, float defense, const std::string& corpse_name) :
    Destructible(max_hp, defense, corpse_name)
{}

void PlayerDestructible::die(pat::Actor* owner, pat::Engine* engine)
{
    engine->get_gui()->message(TCODColor::red, owner->get_name(), " is dead");
    Destructible::die(owner, engine);
}

PlayerDestructible* PlayerDestructible::clone_impl() const
{
    return new PlayerDestructible(*this);
}