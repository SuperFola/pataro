#ifndef COMPONENTS_AI_CONFUSEDMONSTER_HPP
#define COMPONENTS_AI_CONFUSEDMONSTER_HPP

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
    class ConfusedMonsterAI : public AI
    {
    public:
        /**
         * @brief Construct a new Confused Monster AI object
         * 
         * @param nb_turns confusion turns count
         * @param old_ai to be able to restore the previous AI
         */
        ConfusedMonsterAI(int nb_turns, std::unique_ptr<AI>&& old_ai);

        /**
         * @brief Update an entity with no intelligence
         * 
         * @param owner 
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<Action> update(Entity* owner, Engine* engine) override;

    protected:
        [[nodiscard]] ConfusedMonsterAI* clone_impl() const override;

    private:
        int m_nb_turns;
        std::unique_ptr<AI> m_old = nullptr;
    };
}

#endif
