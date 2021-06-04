#ifndef PATARO_COMPONENTS_AI_MONSTER_HPP
#define PATARO_COMPONENTS_AI_MONSTER_HPP

#include <Pataro/Components/AI.hpp>
#include <Pataro/Action.hpp>

#include <memory>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class MonsterAI : public AI
    {
    public:
        /**
         * @brief Update an entity with some intelligence
         * 
         * @param owner 
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<Action> update(Entity* owner, Engine* engine) override;

    protected:
        virtual MonsterAI* clone_impl() const override;

    private:
        /**
         * @brief Move the monster around, or if possible, attack
         * 
         * @param owner 
         * @param x position of the wanted destination
         * @param y position of the wanted destination
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<Action> move_or_attack(Entity* owner, int x, int y, Engine* engine);

        int m_move_count;
    };
}

#endif
