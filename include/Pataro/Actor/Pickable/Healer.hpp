#ifndef PATARO_ACTOR_PICKABLE_HEALER_HPP
#define PATARO_ACTOR_PICKABLE_HEALER_HPP

#include <Pataro/Actor/Pickable.hpp>

namespace pat
{
    class Actor;
    class Engine;
}

namespace pat::actor::details
{
    class Healer : public Pickable
    {
    public:
        /**
         * @brief Construct a new Healer object
         * 
         * @param amount damage to heal
         */
        Healer(float amount);

        /**
         * @brief Use the healing object
         * 
         * @param owner 
         * @param wearer 
         * @param engine 
         * @return true 
         * @return false 
         */
        bool use(Actor* owner, Actor* wearer, Engine* engine) override;

    protected:
        virtual Healer* clone_impl() const override;

    private:
        float m_amount;
    };
}

#endif
