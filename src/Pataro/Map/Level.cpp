#include <Pataro/Map/Level.hpp>

#include <libtcod.hpp>

using namespace pat::map;

Level::Level(int width, int height) :
    m_width(width), m_height(height),
    m_tiles(width * height, map::Tile(/* can_walk */ false))
{}

bool Level::is_wall(int x, int y) const
{
    if (x >= 0 && y >= 0 && x < m_width && y < m_height)
        return !m_tiles[x + y * m_width].can_walk;
    return true;  // anything outside the map region is a wall
}

void Level::render() const
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

void Level::dig(int x, int y, int w, int h)
{
    for (int xx = x; xx < x + w; ++xx)
    {
        for (int yy = y; yy < y + h; ++yy)
            m_tiles[xx + yy * m_width].can_walk = true;
    }
