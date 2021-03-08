#ifndef PATARO_ACTIONS_LIGHTNINGBOLT_HPP
#define PATARO_ACTIONS_LIGHTNINGBOLT_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::action
{
    class LightningBoltAction : public Action
    {
    public:
        /**
         * @brief Construct a new Lightning Bolt Action object
         * 
         * @param source 
         * @param owner 
         * @param range 
         * @param damage 
         */
        LightningBoltAction(Entity* source, Entity* owner, float range, float damage);

        /**
         * @brief Launch the lightning!
         * 
         * @param engine 
         * @return ActionResult 
         */
        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        Entity* m_owner;
        float m_range;
        float m_damage;
    };
}

#endif
