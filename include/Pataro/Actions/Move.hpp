#ifndef PATARO_ACTIONS_MOVE_HPP
#define PATARO_ACTIONS_MOVE_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Engine;
    class Entity;
}

namespace pat::action
{
    class MoveAction : public Action
    {
    public:
        /**
         * @brief Construct a new Move Action object
         * 
         * @param source the entity which triggered the action
         * @param dx delta x
         * @param dy delta y
         */
        MoveAction(Entity* source, int dx, int dy);

        /**
         * @brief Perform the action
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        int m_dx, m_dy;
    };
}

#endif
