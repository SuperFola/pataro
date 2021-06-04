#ifndef PATARO_ACTIONS_HEAL_HPP
#define PATARO_ACTIONS_HEAL_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat
{
    class HealAction : public Action
    {
    public:
        /**
         * @brief Construct a new Heal Action object
         * 
         * @param source 
         * @param owner the entity to heal
         * @param quantity hp to heal
         */
        HealAction(Entity* source, Entity* owner, float quantity);

        /**
         * @brief Perform the healing
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        Entity* m_owner;
        float m_quantity;
    };
}

#endif
