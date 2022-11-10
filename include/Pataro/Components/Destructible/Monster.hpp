#ifndef COMPONENTS_DESTRUCTIBLE_MONSTER_HPP
#define COMPONENTS_DESTRUCTIBLE_MONSTER_HPP

#include <Pataro/Components/Destructible.hpp>

#include <cereal/archives/xml.hpp>
#include <cereal/types/polymorphic.hpp>

#include <string>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class MonsterDestructible : public Destructible
    {
    public:
        /**
         * @brief Construct a new Monster Destructible object
         * 
         * @param max_hp 
         * @param defense 
         * @param corpse_name 
         */
        MonsterDestructible(float max_hp, float defense, const std::string& corpse_name);

        void die(Entity* owner, Engine* engine) override;

        template <class Archive>
        void serialize(Archive& ar)
        {
             ar(cereal::base_class<Destructible>(this));
        };


    protected:
        virtual MonsterDestructible* clone_impl() const override;
    };
}

CEREAL_REGISTER_DYNAMIC_INIT(pataro)
CEREAL_REGISTER_TYPE(pat::component::MonsterDestructible)
CEREAL_REGISTER_POLYMORPHIC_RELATION(pat::component::Destructible, pat::component::MonsterDestructible)

#endif
