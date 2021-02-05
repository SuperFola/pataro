#include <Pataro/Map/Map.hpp>

#include <Pataro/Map/Constants.hpp>

#include <libtcod.hpp>

using namespace pat;

Map::Map(std::size_t depth)
{
    // create levels
    for (std::size_t i = 0; i < depth; ++i)
        m_levels.emplace_back(map::details::level_w, map::details::level_h);
}

bool Map::is_wall(int x, int y) const
{
    return m_levels[m_current].is_wall(x, y);
}

void Map::render() const
{
    m_levels[m_current].render();
}
