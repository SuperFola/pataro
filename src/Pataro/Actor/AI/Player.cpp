#include <Pataro/Actor/AI/Player.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Actor/Destructible.hpp>

#include <iostream>

using namespace pat::actor::details;

void PlayerAI::update(pat::Actor* owner, pat::Engine* engine)
{
    if (Destructible* d = owner->destructible(); d != nullptr && d->is_dead())
        return;

    int dx = 0,
        dy = 0;

    switch (key.vk)
    {
        case TCODK_UP:    --dy; break;
        case TCODK_DOWN:  ++dy; break;
        case TCODK_LEFT:  --dx; break;
        case TCODK_RIGHT: ++dx; break;
        default:                break;
    }

    // if we were able to move, compute a new game state and field of view
    if (dy != 0 || dx != 0)
    {
        engine->change_state(pat::GameState::NewTurn);

        if (move_or_attack(owner, dx, dy, engine->get_map()))
            engine->get_map()->compute_fov(owner->get_x(), owner->get_y(), m_fov_radius);
    }
}

bool PlayerAI::move_or_attack(Actor* owner, int dx, int dy, Engine* engine)
{
    if (engine->get_map()->is_wall(m_x + dx, m_y + dy))
        return false;

    if (Actor* a = engine->get_map()->get_actor(m_x + dx, m_y + dy); a != nullptr)
    {
        Destructible* d = a->destructible();

        // found a possible ennemy, attack it
        if (d != nullptr && !d->is_dead())
        {
            owner->attacker()->attack(owner, a);
            return false;
        }
        else if (d != nullptr && d->is_dead())
        {
            std::cout << "There is a " << a->get_name() << " here\n";
        }
    }

    m_x += dx;
    m_y += dy;

    return true;
}
