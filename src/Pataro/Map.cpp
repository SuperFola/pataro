#include <Pataro/Map.hpp>

#include <Pataro/Map/Constants.hpp>

#include <libtcod.hpp>

using namespace pat;

Map::Map(std::size_t depth) :
    m_current(0)
{
    // create levels
    for (std::size_t i = 0; i < depth; ++i)
        m_levels.emplace_back(map::details::level_w, map::details::level_h);

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

void Map::compute_fov(int x, int y, int fov_radius)
{
    m_levels[m_current].compute_fov(x, y, fov_radius);
}

void Map::render()
{
    m_levels[m_current].render();
}

map::Level& Map::current_level()
{
    return m_levels[m_current];
}