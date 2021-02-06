#include <Pataro/Actor/AI/Monster.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Actor/Destructible.hpp>
#include <Pataro/Actor/Attacker.hpp>
#include <Pataro/Constants.hpp>

#include <iostream>
#include <cmath>

using namespace pat::actor::details;

void MonsterAI::update(pat::Actor* owner, pat::Engine* engine)
{
    if (Destructible* d = owner->destructible(); d != nullptr && d->is_dead())
        return;

    // the monster is in the field of view of the player
    // thus it should go toward it
    if (engine->get_map()->is_in_fov(owner->get_x(), owner->get_y()))
        move_or_attack(
            owner,
            engine->get_player()->get_x(),
            engine->get_player()->get_y(),
            engine
        );
}

void MonsterAI::move_or_attack(pat::Actor* owner, int x, int y, pat::Engine* engine)
{
    // TODO improve monster pathfinding later
    int dx = x - owner->get_x(),
        dy = y - owner->get_y();

    float distance = std::sqrt(static_cast<float>(dx * dx + dy * dy));
    if (distance >= 2.f)
    {
        dx = static_cast<int>(std::round(dx / distance));
        dy = static_cast<int>(std::round(dy / distance));

        if (engine->get_map()->can_walk(owner->get_x() + dx, owner->get_y() + dy))
            owner->put_at(owner->get_x() + dx, owner->get_y() + dy);
        else if (Attacker* a = owner->attacker(); a != nullptr)
            a->attack(owner, engine->get_player(), engine->get_map());
    }
}
