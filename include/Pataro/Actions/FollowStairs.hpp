#ifndef PATARO_ACTIONS_FOLLOWSTAIRS_HPP
#define PATARO_ACTIONS_FOLLOWSTAIRS_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Engine;
    class Entity;

    class FollowStairsAction : public Action
    {
    public:
        enum class Direction
        {
            Up,
            Down
        };

        /**
         * @brief Construct a new Follow Stairs Action object
         * 
         * @param source can only be the player
         * @param direction 
         */
        FollowStairsAction(Entity* source, Direction direction);

        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        Direction m_direction;
    };
}


#endif
