#ifndef PATARO_ACTIONS_FIREBALL_HPP
#define PATARO_ACTIONS_FIREBALL_HPP

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
    class FireballAction : public Action
    {
    public:
        /**
         * @brief Construct a new Fireball Action object
         * 
         * @param source 
         * @param owner 
         * @param picker 
         * @param damage 
         */
        FireballAction(Entity* source, Entity* owner, const component::PickTile* picker, float damage);

        /**
         * @brief Launch the fireball
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        Entity* m_owner;
        int m_tx, m_ty;
        float m_range;
        float m_damage;
    };
}

#endif
