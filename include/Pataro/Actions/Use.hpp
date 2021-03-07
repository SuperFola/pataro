#ifndef PATARO_ACTIONS_USEACTION_HPP
#define PATARO_ACTIONS_USEACTION_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Engine;
    class Entity;
}

namespace pat::action
{
    class UseAction : public Action
    {
    public:
        /**
         * @brief Construct a new Use Action object
         * 
         * @param owner 
         * @param object the object to use
         */
        UseAction(Entity* owner, Entity* object);

        /**
         * @brief Use the object
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
