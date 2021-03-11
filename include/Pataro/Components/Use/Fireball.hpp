#ifndef COMPONENTS_USE_FIREBALL_HPP
#define COMPONENTS_USE_FIREBALL_HPP

#include <Pataro/Components/Use.hpp>
#include <Pataro/Action.hpp>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component::details
{
    class FireballUse : public Use
    {
    public:
        /**
         * @brief Construct a new Fireball Use object
         * 
         * @param range 
         * @param damage 
         */
        FireballUse(float range, float damage);

    protected:
        /**
         * @brief Use the fireball
         * 
         * @param source 
         * @param owner 
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<Action> use(Entity* source, Entity* owner, Engine* engine) override;

        FireballUse* clone_impl() const override;

    private:
        float m_range;
        float m_damage;
    };
}

#endif
