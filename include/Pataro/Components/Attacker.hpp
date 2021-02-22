#ifndef PATARO_COMPONENTS_ATTACKER_HPP
#define PATARO_COMPONENTS_ATTACKER_HPP

#include <memory>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class Attacker
    {
    public:
        /**
         * @brief Construct a new Attacker object
         * 
         * @param power 
         */
        Attacker(float power);

        /**
         * @brief The owner is attacking a given target
         * 
         * @param owner 
         * @param target 
         * @param engine 
         */
        void attack(Entity* owner, Entity* target, Engine* engine);

    private:
        float m_power;
    };
}

#endif
