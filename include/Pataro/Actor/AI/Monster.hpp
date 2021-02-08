#ifndef PATARO_ACTOR_AI_MONSTER_HPP
#define PATARO_ACTOR_AI_MONSTER_HPP

#include <Pataro/Actor/AI.hpp>

namespace pat
{
    class Actor;
    class Engine;
}

namespace pat::actor::details
{
    class MonsterAI : public AI
    {
    public:
        /**
         * @brief Update an entity with some intelligence
         * 
         * @param owner 
         * @param engine 
         */
        void update(Actor* owner, Engine* engine) override;

    private:
        /**
         * @brief Move the monster around, or if possible, attack
         * 
         * @param owner 
         * @param x position of the wanted destination
         * @param y position of the wanted destination
         * @param engine 
         */
        void move_or_attack(Actor* owner, int x, int y, Engine* engine);

        int m_move_count;
    };
}

#endif
