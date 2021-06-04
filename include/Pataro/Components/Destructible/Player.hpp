#ifndef PATARO_COMPONENTS_DESTRUCTIBLE_PLAYER_HPP
#define PATARO_COMPONENTS_DESTRUCTIBLE_PLAYER_HPP

#include <Pataro/Components/Destructible.hpp>

#include <string>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class PlayerDestructible : public Destructible
    {
    public:
        /**
         * @brief Construct a new Player Destructible object
         * 
         * @param max_hp 
         * @param defense 
         * @param corpse_name 
         */
        PlayerDestructible(float max_hp, float defense, const std::string& corpse_name);

        void die(Entity* owner, Engine* engine);

    protected:
        virtual PlayerDestructible* clone_impl() const override;
    };
}

#endif
