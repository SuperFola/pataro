#ifndef PATARO_ACTIONS_ATTACK_HPP
#define PATARO_ACTIONS_ATTACK_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Engine;
    class Entity;
}

namespace pat
{
    class AttackAction : public Action
    {
    public:
        /**
         * @brief Construct a new Attack Action object
         * 
         * @param source the entity which triggered the action
         * @param target the entity to attack
         */
        AttackAction(Entity* source, Entity* target);

        /**
         * @brief Perform the action
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        Entity* m_target;
    };
}

#endif
