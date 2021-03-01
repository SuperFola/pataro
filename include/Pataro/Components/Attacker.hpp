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

        inline float power() const { return m_power; }

    private:
        float m_power;
    };
}

#endif
