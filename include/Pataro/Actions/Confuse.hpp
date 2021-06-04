#ifndef PATARO_ACTIONS_CONFUSE_HPP
#define PATARO_ACTIONS_CONFUSE_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Entity;
    class Engine;

    namespace component
    {
        class PickTile;
    }
}

namespace pat
{
    class ConfuseAction : public Action
    {
    public:
        /**
         * @brief Construct a new Confuse Action object
         * 
         * @param source 
         * @param owner 
         * @param picker 
         * @param nb_turns 
         */
        ConfuseAction(Entity* source, Entity* owner, const component::PickTile* picker, int nb_turns);

        /**
         * @brief Confuse
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        Entity* m_owner;
        Entity* m_target;
        int m_nb_turns;
    };
}

#endif
