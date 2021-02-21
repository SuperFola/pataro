#ifndef PATARO_ACTOR_ATTACKER_HPP
#define PATARO_ACTOR_ATTACKER_HPP

#include <memory>

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

        /**
         * @brief Clone the class
         * 
         * @return std::unique_ptr<Attacker> 
         */
        inline std::unique_ptr<Attacker> clone() const { return std::unique_ptr<Attacker>(clone_impl()); }

    protected:
        virtual Attacker* clone_impl() const;

    private:
        float m_power;
    };
}

#endif
