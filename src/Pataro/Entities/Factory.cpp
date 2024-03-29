#include <Pataro/Entities/Factory.hpp>

#include <Pataro/Colors.hpp>

#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Destructible/Monster.hpp>
#include <Pataro/Components/AI/Monster.hpp>

#include <Pataro/Components/Use/OneTime.hpp>
#include <Pataro/Components/Use/OneTimeSelect.hpp>

#include <Pataro/Actions/Heal.hpp>
#include <Pataro/Actions/LightningBolt.hpp>
#include <Pataro/Actions/Fireball.hpp>
#include <Pataro/Actions/Confuse.hpp>

#include <cmath>

using namespace pat::entity;

Factory::Factory() :
    m_rng(TCODRandom::getInstance())
{}

std::shared_ptr<pat::Entity> Factory::get_random_monster(int x, int y, float difficulty)
{
    std::shared_ptr<Entity> entity;
    float biaised_difficulty = std::sqrt(difficulty);
    int rdm = m_rng->getInt(0, 100);

    // create an orc
    if (rdm < 80)
    {
        entity = std::make_shared<Entity>(x, y, 'o', "orc", colors::desaturatedGreen);
        entity->set_attacker<component::Attacker>(
            3.0f * biaised_difficulty
        );
        entity->set_destructible<component::MonsterDestructible>(
            10.0f * biaised_difficulty,
            0.5f * (biaised_difficulty - 1.0f),
            "dead orc"
        );
    }
    // create a troll
    else
    {
        entity = std::make_shared<Entity>(x, y, 'T', "troll", colors::darkerGreen);
        entity->set_attacker<component::Attacker>(
            4.0f * biaised_difficulty
        );
        entity->set_destructible<component::MonsterDestructible>(
            16.0f * biaised_difficulty,
            1.0f * biaised_difficulty,
            "troll carcass"
        );
    }

    entity->set_ai<component::MonsterAI>();

    return entity;
}

std::shared_ptr<pat::Entity> Factory::get_random_item(int x, int y)
{
    std::shared_ptr<Entity> entity;
    int rdm = m_rng->getInt(0, 100);

    if (rdm < 70)
    {
        entity = std::make_shared<Entity>(x, y, '!', "Health potion", colors::violet);
        entity->set_blocking(false);
        entity->set_use<component::OneTimeUse<HealAction, float>>(4.f);
    }
    else if (rdm < 80)
    {
        entity = std::make_shared<Entity>(x, y, '#', "Scroll of lightning bolt", colors::darkOrange);
        entity->set_blocking(false);
        entity->set_use<component::OneTimeUse<LightningBoltAction, float, float>>(5.f, 20.f);
    }
    else if (rdm < 90)
    {
        entity = std::make_shared<Entity>(x, y, '#', "Scroll of fireball", colors::lightYellow);
        entity->set_blocking(false);
        entity->set_use<component::OneTimeSelectUse<FireballAction, float>>(
            "a target tile for the fireball",
            component::PickTile(component::PickMethod::Simple, /* range */ 2.f),
            /* damage */ 12.f
        );
    }
    else
    {
        entity = std::make_shared<Entity>(x, y, '#', "Scroll of confusion", colors::lightGreen);
        entity->set_blocking(false);
        entity->set_use<component::OneTimeSelectUse<ConfuseAction, int>>(
            "an ennemy to confuse",
            component::PickTile(component::PickMethod::LivingEntity, /* range */ 5.0f),
            /* turns count */ 3
        );
    }

    return entity;
}