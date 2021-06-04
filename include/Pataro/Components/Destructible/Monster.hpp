#ifndef PATARO_COMPONENTS_DESTRUCTIBLE_MONSTER_HPP
#define PATARO_COMPONENTS_DESTRUCTIBLE_MONSTER_HPP

#include <Pataro/Components/Destructible.hpp>

#include <string>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
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

        void die(Entity* owner, Engine* engine) override;

    protected:
        virtual MonsterDestructible* clone_impl() const override;
    };
}

#endif
