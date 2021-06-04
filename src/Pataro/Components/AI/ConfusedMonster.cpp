#include <Pataro/Components/AI/ConfusedMonster.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Actions/Move.hpp>

using namespace pat::component;

ConfusedMonsterAI::ConfusedMonsterAI(int nb_turns, std::unique_ptr<AI>&& old_ai) :
    m_nb_turns(nb_turns), m_old(std::move(old_ai))
{}

std::unique_ptr<pat::Action> ConfusedMonsterAI::update(pat::Entity* owner, pat::Engine* engine)
{
    // do nothing if we're dead
    if (Destructible* d = owner->destructible(); d != nullptr && d->is_dead())
        return nullptr;

    int x = owner->get_x(),
        y = owner->get_y();

    TCODRandom* rng = TCODRandom::getInstance();
    int dx = rng->getInt(-1, 1),
        dy = rng->getInt(-1, 1);

    if ((dx != 0 || dy != 0) && engine->get_map()->can_walk(x + dx, y + dy))
        return std::make_unique<pat::MoveAction>(owner, dx, dy);

    --m_nb_turns;
    if (m_nb_turns <= 0)
        owner->set_ai(std::move(m_old));

    return nullptr;
}

ConfusedMonsterAI* ConfusedMonsterAI::clone_impl() const
{
    return new ConfusedMonsterAI(m_nb_turns, m_old ? m_old->clone() : nullptr);
}
