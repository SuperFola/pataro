#ifndef PATARO_ACTOR_DESTRUCTIBLE_HPP
#define PATARO_ACTOR_DESTRUCTIBLE_HPP

#include <string>

namespace pat
{
    class Actor;
    class Map;
}

namespace pat::actor
{
    class Destructible
    {
    public:
        /**
         * @brief Construct a new Destructible object
         * 
         * @param max_hp 
         * @param defense 
         * @param corpse_name the name of the actor once dead
         */
        Destructible(float max_hp, float defense, const std::string& corpse_name);

        /**
         * @brief Handles damages given to the destructible
         * 
         * @param owner 
         * @param damage 
         * @param map 
         * @return float the number of hit points actually taken
         */
        float take_damage(Actor* owner, float damage, Map* map);

        /**
         * @brief What happens when the owning entity dies is handled here
         * 
         * @param owner 
         * @param map 
         */
        virtual void die(Actor* owner, Map* map);

        inline bool is_dead() { return m_hp <= 0.f; }
        inline float defense() { return m_defense; }

    private:
        float m_max_hp, m_hp;
        float m_defense;
        std::string m_corpse_name;  ///< The actor's name once dead
    };
}

#endif
