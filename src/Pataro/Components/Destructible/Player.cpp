#include <Pataro/Components/Destructible/Player.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::component::details;

PlayerDestructible::PlayerDestructible(float max_hp, float defense, const std::string& corpse_name) :
    Destructible(max_hp, defense, corpse_name)
{}

void PlayerDestructible::die(pat::Entity* owner, pat::Engine* engine)
{
    engine->get_gui()->message(TCODColor::red, owner->get_name(), " is dead");
    Destructible::die(owner, engine);
}

PlayerDestructible* PlayerDestructible::clone_impl() const
{
    return new PlayerDestructible(*this);
}