#include <Pataro/Actions/FollowStairs.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Constants.hpp>

using namespace pat;

FollowStairsAction::FollowStairsAction(Entity* source, FollowStairsAction::Direction direction) :
    m_source(source), m_direction(direction)
{}

ActionResult FollowStairsAction::perform(Engine* engine)
{
    if (m_source != engine->get_player())
        return ActionResult::Fail;

    Map* map = engine->get_map();

    switch (m_direction)
    {
        case Direction::Up:
            if (map->move_upstairs(m_source))
            {
                engine->get_gui()->message(colors::lightBlue, "You moved upstairs");
                if (map->floor() == 0)
                    engine->get_gui()->message(colors::lightAmber, "You are on the ground floor");

                int x = m_source->get_x();
                int y = m_source->get_y();
                engine->get_map()->compute_fov(x, y, details::player_fov);
                return ActionResult::Success;
            }
            break;

        case Direction::Down:
            if (map->move_downstairs(m_source))
            {
                if (map->is_bottom_floor())
                    engine->get_gui()->message(colors::lightAmber, "You have reached the depths of the dungeon");
                else
                    engine->get_gui()->message(colors::lightBlue, "You moved downstairs");

                int x = m_source->get_x();
                int y = m_source->get_y();
                engine->get_map()->compute_fov(x, y, details::player_fov);
                return ActionResult::Success;
            }
            break;
    }

    return ActionResult::Fail;
}
