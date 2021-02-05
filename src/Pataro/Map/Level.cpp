#include <Pataro/Map/Level.hpp>
#include <Pataro/Map/BSPListener.hpp>
#include <Pataro/Map/Constants.hpp>

using namespace pat::map;

Level::Level(int width, int height) :
    m_width(width), m_height(height),
    m_tiles(width * height, details::Tile())
{}

bool Level::is_wall(int x, int y) const
{
    // already checks for the bounds
    return !m_map->isWalkable(x, y);
}

bool Level::can_walk(int x, int y) const
{
    if (is_wall(x, y))
        return false;

    for (const std::unique_ptr<Actor>& actor : m_actors)
    {
        if (actor->get_x() == x && actor->get_y() == y)
            return false;
    }
    return true;
}

bool Level::is_in_fov(int x, int y)
{
    if (m_map->isInFov(x, y))
    {
        m_tiles[x + y * m_width].explored = true;
        return true;
    }
    return false;
}

bool Level::is_explored(int x, int y) const
{
    if (x >= 0 && y >= 0 && x < m_width && y < m_height)
        return m_tiles[x + y * m_width].explored;
    return false;  // tiles outside the world are unexplored
}

void Level::compute_fov(int x, int y, int fov_radius)
{
    m_map->computeFov(x, y, fov_radius);
}

void Level::render()
{
    // TODO clean up
    static const TCODColor darkWall(0, 0, 100);
    static const TCODColor darkGround(50, 50, 150);
    static const TCODColor lightWall(130, 110, 50);
    static const TCODColor lightGround(200, 180, 50);

    for (int x = 0; x < m_width; ++x)
    {
        for (int y = 0; y < m_height; ++y)
        {
            if (is_in_fov(x, y))
                TCODConsole::root->setCharBackground(x, y, is_wall(x, y) ? lightWall : lightGround);
            else if (is_explored(x, y))
                TCODConsole::root->setCharBackground(x, y, is_wall(x, y) ? darkWall : darkGround);
        }
    }

    for (const std::unique_ptr<Actor>& actor : m_actors)
    {
        if (m_map->isInFov(actor->get_x(), actor->get_y()))
            actor->render();
    }
}

const details::Room& Level::get_first_room() const
{
    return m_rooms[0];
}

pat::Actor* Level::create_player(int ch, const TCODColor& color)
{
    // put it in the middle of the maze
    m_actors.emplace_back(std::make_unique<Actor>(
        m_rooms[0].x +  m_rooms[0].width / 2,
        m_rooms[0].y +  m_rooms[0].height / 2,
        ch,
        "Player",
        color
    ));

    return m_actors.back().get();
}

void Level::generate()
{
    m_map = std::make_unique<TCODMap>(m_width, m_height);

    // generate the level
    TCODBsp bsp(0, 0, m_width, m_height);
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
            // transparent & walkable
            m_map->setProperties(x, y, true, true);
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

    TCODRandom* rng = TCODRandom::getInstance();
    int nb_monsters = rng->getInt(0, details::max_room_monsters);

    while (nb_monsters > 0)
    {
        int x = rng->getInt(x1, x2);
        int y = rng->getInt(y1, y2);
        if (can_walk(x, y))
        {
            if (rng->getInt(0, 100) < 80)
                // create an orc
                m_actors.emplace_back(std::make_unique<Actor>(x, y, 'o', "orc", TCODColor::desaturatedGreen));
            else
                // create a troll
                m_actors.emplace_back(std::make_unique<Actor>(x, y, 'T', "troll", TCODColor::darkerGreen));
        }
        --nb_monsters;
    }
}
