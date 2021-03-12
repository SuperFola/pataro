#include <Pataro/Components/Use/Confuser.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Actions/Confuse.hpp>

using namespace pat::component::details;

ConfuserUse::ConfuserUse(int nb_turns, float range) :
    m_nb_turns(nb_turns), m_range(range)
{}

std::unique_ptr<pat::Action> ConfuserUse::use(pat::Entity* source, pat::Entity* owner, pat::Engine* engine)
{
    engine->get_gui()->message(TCODColor::cyan, "Left-click an ennemy to confuse it,\nor right-click to cancel.");
    int x, y;
    if (!engine->pick_a_tile(&x, &y, m_range))
        return nullptr;

    pat::Entity* entity = engine->get_map()->get_entity(x, y);
    if (entity->destructible() == nullptr || entity->destructible()->is_dead())
        return nullptr;

    return std::make_unique<pat::action::ConfuseAction>(
        source,
        owner,
        entity,
        m_nb_turns
    );
}

ConfuserUse* ConfuserUse::clone_impl() const
{
    return new ConfuserUse(*this);
}