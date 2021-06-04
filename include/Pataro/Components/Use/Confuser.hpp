#ifndef COMPONENTS_USE_CONFUSER_HPP
#define COMPONENTS_USE_CONFUSER_HPP

#include <Pataro/Components/Use.hpp>
#include <Pataro/Action.hpp>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class ConfuserUse : public Use
    {
    public:
        /**
         * @brief Construct a new Confuser Use object
         * 
         * @param nb_turns 
         * @param range 
         */
        ConfuserUse(int nb_turns, float range);

    protected:
        /**
         * @brief Use the scroll of confusion
         * 
         * @param source 
         * @param owner 
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<Action> use(Entity* source, Entity* owner, Engine* engine) override;

        ConfuserUse* clone_impl() const override;

    private:
        int m_nb_turns;
        float m_range;
    };
}

#endif
