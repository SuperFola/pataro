#include <Pataro/Map/Map.hpp>

#include <libtcod.hpp>

using namespace pat;

Map::Map(std::size_t depth)
{
    // TODO generate levels
}

bool Map::is_wall(int x, int y) const
{
    return m_levels[m_current].is_wall(x, y);
}

void Map::render() const
{
    m_levels[m_current].render();
}
