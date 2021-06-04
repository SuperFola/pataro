#include <Pataro/Components/Use/OneTimeSelect.hpp>

using namespace pat::component;

PickTile::PickTile(PickMethod method, float range) :
    m_method(method), m_range(range), m_entity(nullptr)
{}

bool PickTile::pick(pat::Engine* engine)
{
    switch (m_method)
    {
        case PickMethod::Simple:
            return simple(engine);

        case PickMethod::LivingEntity:
            return liveEntity(engine);
    }

    return false;
}

bool PickTile::simple(pat::Engine* engine)
{
    return engine->pick_a_tile(&m_x, &m_y, m_range);
}

bool PickTile::liveEntity(pat::Engine* engine)
{
    if (!simple(engine))
        return false;

    m_entity = engine->get_map()->get_entity(m_x, m_y);
    if (m_entity->destructible() == nullptr || m_entity->destructible()->is_dead())
        return false;
    return true;
}