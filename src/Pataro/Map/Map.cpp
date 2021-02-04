#include <Pataro/Map/Map.hpp>

#include <libtcod.hpp>

using namespace pat;

Map::Map(int width, int height) :
    m_width(width), m_height(height)
{
    m_tiles.reserve(width * height);
    // TODO remove
    set_wall(30, 22);
    set_wall(50, 22);
}

bool Map::is_wall(int x, int y) const
{
    if (x < m_width && y < m_height)
        return !m_tiles[x + y * m_width].can_walk;
    return true;  // anything outside the map region is a wall
}

void Map::render() const
{
    // TODO clean up
    static const TCODColor darkWall(0, 0, 100);
    static const TCODColor darkGround(50, 50, 150);

    for (int x = 0; x < m_width; ++x)
    {
        for (int y = 0; y < m_height; ++y)
        {
            if (is_wall(x, y))
                TCODConsole::root->setCharBackground(x, y, darkWall);
            else
                TCODConsole::root->setCharBackground(x, y, darkGround);
        }
    }
}

void Map::set_wall(int x, int y)
{
    m_tiles[x + y * m_width].can_walk = false;
}