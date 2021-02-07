#ifndef PATARO_ACTOR_AI_HPP
#define PATARO_ACTOR_AI_HPP

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
    };
}

#endif
