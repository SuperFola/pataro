#ifndef PATARO_ACTIONS_DROP_HPP
#define PATARO_ACTIONS_DROP_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Engine;
    class Entity;
}

namespace pat
{
    class DropAction : public Action
    {
    public:
        /**
         * @brief Construct a new Drop Action object
         * 
         * @param owner 
         * @param object the object to drop
         */
        DropAction(Entity* owner, Entity* object);

        /**
         * @brief Perform the action
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_owner;
        Entity* m_object;
    };
}

#endif
