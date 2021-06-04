#ifndef PATARO_ACTIONS_PICKUP_HPP
#define PATARO_ACTIONS_PICKUP_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Engine;
    class Entity;
}

namespace pat
{
    class PickUpAction : public Action
    {
    public:
        /**
         * @brief Construct a new Pick Up Action object
         * 
         * @param source the entity trying to pick up something
         * @param x position of the entity
         * @param y position of the entity
         */
        PickUpAction(Entity* source, int x, int y);

        /**
         * @brief Tries to pick the object up and put it in the source container
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        int m_x, m_y;
    };
}

#endif
