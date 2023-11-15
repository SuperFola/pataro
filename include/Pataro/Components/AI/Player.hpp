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

namespace pat::component
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

    protected:
        /**
         * @brief Handle keyboard actions
         * 
         * @param owner 
         * @param engine 
         * @param keycode sdl2 keycode
         * @return std::unique_ptr<pat::Action> 
         */
        std::unique_ptr<pat::Action> handle_action_key(Entity* owner, Engine* engine, int keycode);

        [[nodiscard]] PlayerAI* clone_impl() const override;
    };
}

#endif
