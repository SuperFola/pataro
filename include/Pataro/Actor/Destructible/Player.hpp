#ifndef PATARO_ACTOR_DESTRUCTIBLE_PLAYER_HPP
#define PATARO_ACTOR_DESTRUCTIBLE_PLAYER_HPP

#include <Pataro/Actor/Destructible.hpp>

#include <string>

namespace pat
{
    class Actor;
    class Map;
}

namespace pat::actor::details
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

        void die(Actor* owner, Map* map);
    };
}

#endif
