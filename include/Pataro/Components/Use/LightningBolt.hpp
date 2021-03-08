#ifndef COMPONENTS_USE_LIGHTNINGBOLT_HPP
#define COMPONENTS_USE_LIGHTNINGBOLT_HPP

#include <Pataro/Components/Use.hpp>
#include <Pataro/Action.hpp>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component::details
{
    class LightningBoltUse : public Use
    {
    public:
        /**
         * @brief Construct a new Lightning Bolt Use object
         * 
         * @param range 
         * @param damage 
         */
        LightningBoltUse(float range, float damage);

    protected:
        /**
         * @brief Use the lightning bolt
         * 
         * @param source 
         * @param owner 
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<Action> use(Entity* source, Entity* owner, Engine* engine) override;

        LightningBoltUse* clone_impl() const override;

    private:
        float m_range;
        float m_damage;
    };
}

#endif
