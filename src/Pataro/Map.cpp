#include <Pataro/Map.hpp>

#include <Pataro/Engine.hpp>

#include <libtcod.hpp>

using namespace pat;

Map::Map(unsigned width, unsigned height, std::size_t depth) :
    m_current(0)
{
    // create levels
    for (std::size_t i = 0; i < depth; ++i)
        m_levels.emplace_back(width, height);

    // generate the first level
    m_levels[m_current].generate();
}

bool Map::is_wall(int x, int y) const
{
    return m_levels[m_current].is_wall(x, y);
}

bool Map::can_walk(int x, int y) const
{
    // bounds are already checked underneath
    return m_levels[m_current].can_walk(x, y);
}

pat::Entity* Map::get_entity(int x, int y) const
{
    return m_levels[m_current].get_entity(x, y);
}

pat::Entity* Map::get_closest_monster(pat::Entity* from, float range) const
{
    return m_levels[m_current].get_closest_monster(from, range);
}

void Map::compute_fov(int x, int y, int fov_radius)
{
    m_levels[m_current].compute_fov(x, y, fov_radius);
}

bool Map::is_in_fov(int x, int y)
{
    return m_levels[m_current].is_in_fov(x, y);
}

void Map::render(pat::Engine* engine, float dt)
{
    m_levels[m_current].render(engine, dt);
}

void Map::update(pat::Engine* engine)
{
    m_levels[m_current].update(engine);
}
