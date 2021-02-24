#ifndef PATARO_COMPONENTS_AI_PLAYER_HPP
#define PATARO_COMPONENTS_AI_PLAYER_HPP

#include <Pataro/Components/AI.hpp>
#include <Pataro/Action.hpp>

#include <memory>

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
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<pat::Action> update(Entity* owner, Engine* engine) override;

    private:
        /**
         * @brief Move the player around, or if possible, attack
         * 
         * @param owner 
         * @param dx 
         * @param dy 
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<Action> move_or_attack(Entity* owner, int dx, int dy, Engine* engine);
    };
}

#endif
