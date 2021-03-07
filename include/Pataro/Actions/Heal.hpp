#ifndef PATARO_ACTIONS_HEAL_HPP
#define PATARO_ACTIONS_HEAL_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::action
{
    class HealAction : public Action
    {
    public:
        /**
         * @brief Construct a new Heal Action object
         * 
         * @param source 
         * @param quantity hp to heal
         */
        HealAction(Entity* source, float quantity);

        /**
         * @brief Perform the healing
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        float m_quantity;
    };
}

#endif
