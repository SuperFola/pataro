#ifndef PATARO_ACTOR_AI_HPP
#define PATARO_ACTOR_AI_HPP

#include <memory>

namespace pat
{
    class Actor;
    class Engine;
}

namespace pat::actor
{
    class AI
    {
    public:
        virtual ~AI() = default;

        /**
         * @brief Update an entity with some intelligence
         * 
         * @param owner 
         * @param engine 
         */
        virtual void update(Actor* owner, Engine* engine) = 0;

        /**
         * @brief Clone the class
         * 
         * @return std::unique_ptr<AI> 
         */
        inline std::unique_ptr<AI> clone() const { return std::unique_ptr<AI>(clone_impl()); }

    protected:
        virtual AI* clone_impl() const = 0;
    };
}

#endif
