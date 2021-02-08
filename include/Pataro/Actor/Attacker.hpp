#ifndef PATARO_ACTOR_ATTACKER_HPP
#define PATARO_ACTOR_ATTACKER_HPP

namespace pat
{
    class Actor;
    class Engine;
}

namespace pat::actor
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
        void attack(Actor* owner, Actor* target, Engine* engine);

    private:
        float m_power;
    };
}

#endif
