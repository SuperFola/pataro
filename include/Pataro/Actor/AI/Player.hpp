#ifndef PATARO_ACTOR_AI_PLAYER_HPP
#define PATARO_ACTOR_AI_PLAYER_HPP

#include <Pataro/Actor/AI.hpp>

namespace pat
{
    class Actor;
    class Engine;
}

namespace pat::actor::details
{
    class PlayerAI : public AI
    {
    public:
        /**
         * @brief Move the player around using the keyboard inputs
         * 
         * @param owner 
         * @param engine 
         */
        void update(Actor* owner, Engine* engine) override;

    private:
        bool move_or_attack(Actor* owner, int dx, int dy, Engine* engine);

        int m_fov_radius = 10;
    };
}

#endif
