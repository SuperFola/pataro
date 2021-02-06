#ifndef PATARO_ACTOR_DESTRUCTIBLE_HPP
#define PATARO_ACTOR_DESTRUCTIBLE_HPP

#include <string>

namespace pat
{
    class Actor;
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
         * @return float the number of hit points actually taken
         */
        float take_damage(Actor* owner, float damage);

        /**
         * @brief What happens when the owning entity dies is handled here
         * 
         * @param owner 
         */
        virtual void die(Actor* owner);

        inline bool is_dead() { return m_hp <= 0.f; }

    private:
        float m_max_hp, m_hp;
        float m_defense;
        std::string m_corpse_name;  ///< The actor's name once dead
    };
}

#endif
