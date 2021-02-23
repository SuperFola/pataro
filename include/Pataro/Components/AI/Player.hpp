#ifndef PATARO_COMPONENTS_AI_PLAYER_HPP
#define PATARO_COMPONENTS_AI_PLAYER_HPP

#include <Pataro/Components/AI.hpp>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component::details
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
        void update(Entity* owner, Engine* engine) override;

    private:
        /**
         * @brief Move the player around, or if possible, attack
         * 
         * @param owner 
         * @param dx 
         * @param dy 
         * @param engine 
         * @return true we were able to move
         * @return false 
         */
        bool move_or_attack(Entity* owner, int dx, int dy, Engine* engine);
    };
}

#endif
