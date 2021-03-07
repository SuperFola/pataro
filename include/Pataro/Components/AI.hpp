#ifndef PATARO_COMPONENTS_AI_HPP
#define PATARO_COMPONENTS_AI_HPP

#include <Pataro/Action.hpp>

#include <memory>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
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
         * @return std::unique_ptr<Action> 
         */
        virtual std::unique_ptr<Action> update(Entity* owner, Engine* engine) = 0;

        inline std::unique_ptr<AI> clone() const { return std::unique_ptr<AI>(clone_impl()); }

    protected:
        virtual AI* clone_impl() const = 0;
    };
}

#endif
