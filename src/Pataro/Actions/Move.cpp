#include <Pataro/Actions/Move.hpp>

#include <Pataro/Constants.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Destructible.hpp>

#include <libtcod.hpp>

using namespace pat::action;

MoveAction::MoveAction(pat::Entity* source, int dx, int dy) :
    m_source(source), m_dx(dx), m_dy(dy)
{}

pat::ActionResult MoveAction::perform([[maybe_unused]] pat::Engine* engine)
{
    m_source->move(m_dx, m_dy);

    int x = m_source->get_x(),
        y = m_source->get_y();

    // update player field of view
    if (m_source == engine->get_player())
        engine->get_map()->compute_fov(x, y, pat::details::player_fov);

    if (pat::Entity* e = engine->get_map()->get_entity(x, y); e != nullptr)
    {
        pat::component::Destructible* d = e->destructible();
        if (d != nullptr && d->is_dead())
            engine->get_gui()->message(TCODColor::lightGrey, "There is a ", e->get_name(), " here");
    }

    return pat::ActionResult::Success;
}