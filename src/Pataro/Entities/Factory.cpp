#include <Pataro/Entities/Factory.hpp>

#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Destructible/Monster.hpp>

using namespace pat::entity;

Factory::Factory() :
    m_rng(TCODRandom::getInstance())
{}

std::shared_ptr<pat::Entity> Factory::get_random_monster(int x, int y)
{
    std::shared_ptr<Entity> entity;

    // create an orc
    if (m_rng->getInt(0, 100) < 80)
    {
        entity = std::make_shared<Entity>(x, y, 'o', "orc", TCODColor::desaturatedGreen);
        entity->set_attacker<component::Attacker>(3.0f);
        entity->set_destructible<component::details::MonsterDestructible>(10.0f, 0.0f, "dead orc");
    }
    // create a troll
    else
    {
        entity = std::make_shared<Entity>(x, y, 'T', "troll", TCODColor::darkerGreen);
        entity->set_attacker<component::Attacker>(4.0f);
        entity->set_destructible<component::details::MonsterDestructible>(16.0f, 1.0f, "troll carcass");
    }

    entity->set_ai<component::details::MonsterAI>();

    return entity;
}