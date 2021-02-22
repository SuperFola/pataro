#ifndef PATARO_COMPONENTS_AI_HPP
#define PATARO_COMPONENTS_AI_HPP

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
         */
        virtual void update(Entity* owner, Engine* engine) = 0;
    };
}

#endif
