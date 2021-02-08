#ifndef PATARO_ACTOR_DESTRUCTIBLE_MONSTER_HPP
#define PATARO_ACTOR_DESTRUCTIBLE_MONSTER_HPP

#include <Pataro/Actor/Destructible.hpp>

#include <string>

namespace pat
{
    class Actor;
    class Engine;
}

namespace pat::actor::details
{
    class MonsterDestructible : public Destructible
    {
    public:
        /**
         * @brief Construct a new Monster Destructible object
         * 
         * @param max_hp 
         * @param defense 
         * @param corpse_name 
         */
        MonsterDestructible(float max_hp, float defense, const std::string& corpse_name);

        void die(Actor* owner, Engine* engine) override;
    };
}

#endif
