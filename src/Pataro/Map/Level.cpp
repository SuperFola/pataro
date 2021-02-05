#include <Pataro/Map/Level.hpp>
#include <Pataro/Map/BSPListener.hpp>
#include <Pataro/Map/Constants.hpp>
#include <Pataro/Actor.hpp>

#include <libtcod.hpp>

using namespace pat::map;

Level::Level(int width, int height) :
    m_width(width), m_height(height),
    m_tiles(width * height, details::Tile(/* can_walk */ false))
{
    TCODBsp bsp(0, 0, width, height);
    bsp.splitRecursive(
        // no randomizer
        nullptr,
        // number
        8,
        // max width
        details::room_max_w,
        // max height
        details::room_max_h,
        // max width ratio
        1.5f,
        // max height ratio
        1.5f
    );
    details::BSPListener listener(this);
    bsp.traverseInvertedLevelOrder(static_cast<ITCODBspCallback*>(&listener), nullptr);
}

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

    for (const details::Room& room : m_rooms)
    {
        if (std::optional<Actor> a = room.get_actor(); a.has_value())
            a.value().render();
    }
}

const details::Room& Level::get_first_room() const
{}

void Level::dig(int x1, int y1, int x2, int y2)
{
    if (x2 < x1)
    {
        int x3 = x1;
        x1 = x2;
        x2 = x3;
    }
    if (y2 < y1)
    {
        int y3 = y1;
        y1 = y2;
        y2 = y3;
    }

    for (int x = x1; x <= x2; ++x)
    {
        for (int y = y1; y <= y2; ++y)
        {
            int p = x + y * m_width;
            if (p < m_width * m_height)
                m_tiles[p].can_walk = true;
        }
    }
}

void Level::create_room(bool first_room, int x1, int y1, int x2, int y2)
{
    dig(x1, y1, x2, y2);

    m_rooms.emplace_back(
        (x2 < x1) ? x2 : x1,
        (y2 < y1) ? y2 : y1,
        (x1 > x2) ? x1 - x2 : x2 - x1,
        (y1 > y2) ? y1 - y2 : y2 - y1
    );
}
