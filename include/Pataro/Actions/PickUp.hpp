#ifndef PATARO_ACTIONS_PICKUP_HPP
#define PATARO_ACTIONS_PICKUP_HPP

#include <Pataro/Action.hpp>

namespace pat
{
    class Engine;
    class Entity;
}

namespace pat::action
{
    class PickUpAction : public Action
    {
    public:
        PickUpAction(Entity* source, int x, int y);

        ActionResult perform(Engine* engine) override;

    private:
        Entity* m_source;
        int m_x, m_y;
    };
}

#endif
