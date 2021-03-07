#ifndef COMPONENTS_USE_HEAL_HPP
#define COMPONENTS_USE_HEAL_HPP

#include <Pataro/Action.hpp>
#include <Pataro/Components/Use.hpp>

#include <memory>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component::details
{
    class HealUse : public Use
    {
    public:
        /**
         * @brief Construct a new Heal Use object
         * 
         * @param quantity health points to heal
         */
        HealUse(float quantity);

    protected:
        std::unique_ptr<Action> use(Entity* source, Entity* owner, Engine* engine) override;

        HealUse* clone_impl() const override;

    private:
        float m_quantity;  ///< Quantity of HP to heal
    };
}

#endif
