#include <Pataro/Components/AI/Monster.hpp>

#include <Pataro/Constants.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Constants.hpp>
#include <Pataro/Actions/Move.hpp>
#include <Pataro/Actions/Attack.hpp>

#include <cmath>

using namespace pat::component::details;

std::unique_ptr<pat::Action> MonsterAI::update(pat::Entity* owner, pat::Engine* engine)
{
    // do nothing if we're dead
    if (Destructible* d = owner->destructible(); d != nullptr && d->is_dead())
        return nullptr;

    // the monster is in the field of view of the player
    // thus it should go toward it
    if (engine->get_map()->is_in_fov(owner->get_x(), owner->get_y()))
        m_move_count = tracking_turns;
    else
        --m_move_count;

    if (m_move_count > 0)
        return move_or_attack(
            owner,
            engine->get_player()->get_x(),
            engine->get_player()->get_y(),
            engine
        );

    return nullptr;
}

std::unique_ptr<pat::Action> MonsterAI::move_or_attack(pat::Entity* owner, int xf, int yf, pat::Engine* engine)
{
    int x = owner->get_x(),
        y = owner->get_y();
    int dx = xf - x,
        dy = yf - y;
    // adding wall sliding
    int step_dx = (dx > 0) ? 1 : -1,
        step_dy = (dy > 0) ? 1 : -1;

    pat::Map* map = engine->get_map();

    // tracking the player
    float distance = std::sqrt(static_cast<float>(dx * dx + dy * dy));
    if (distance >= 2.f)
    {
        dx = static_cast<int>(std::round(dx / distance));
        dy = static_cast<int>(std::round(dy / distance));

        if (map->can_walk(x + dx, y + dy))
            return std::make_unique<pat::action::MoveAction>(owner, dx, dy);
        else if (map->can_walk(x + step_dx, y))  // wall sliding 1
            return std::make_unique<pat::action::MoveAction>(owner, step_dx, 0);
        else if (map->can_walk(x, y + step_dy))  // wall sliding 2
            return std::make_unique<pat::action::MoveAction>(owner, 0, step_dy);
    }
    return std::make_unique<pat::action::MoveAction>(owner, dx, dy);
}
