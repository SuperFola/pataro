#include <Pataro/Components/Destructible/Monster.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::component;

MonsterDestructible::MonsterDestructible(float max_hp, float defense, const std::string& corpse_name) :
    Destructible(max_hp, defense, corpse_name)
{}

void MonsterDestructible::die(pat::Entity* owner, pat::Engine* engine)
{
    engine->get_gui()->message(TCODColor::lightGrey, owner->get_name(), " is dead");
    Destructible::die(owner, engine);
}

MonsterDestructible* MonsterDestructible::clone_impl() const
{
    return new MonsterDestructible(*this);
}