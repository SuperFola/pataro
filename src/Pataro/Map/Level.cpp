#include <Pataro/Map/Level.hpp>

#include <Pataro/Map/BSPListener.hpp>
#include <Pataro/Map/Constants.hpp>
#include <Pataro/Map.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Actor/Attacker.hpp>
#include <Pataro/Actor/AI/Monster.hpp>
#include <Pataro/Actor/Destructible.hpp>
#include <Pataro/Actor/Destructible/Monster.hpp>

#include <algorithm>

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

    for (const auto& actor : m_actors)
    {
        if (actor->get_x() == x && actor->get_y() == y && actor->is_blocking())
            return false;
    }
    return true;
}

pat::Actor* Level::get_actor(int x, int y) const
{
    pat::Actor* possibility = nullptr;

    for (const auto& actor : m_actors)
    {
        if (actor->get_x() == x && actor->get_y() == y)
        {
            if (possibility != nullptr)
            {
                actor::Destructible* d = actor->destructible();
                actor::Destructible* dp = possibility->destructible();

                // if there is another possibility which is alive, discard current one

                if (dp != nullptr && dp->is_dead() && !d->is_dead())  // the new one is alive, the old one is dead, keep the alive one
                    possibility = actor.get();
                else if (dp != nullptr && dp->is_dead() && d->is_dead())  // both dead, keep new one because why not
                    possibility = actor.get();
                else if (dp == nullptr && d != nullptr)  // if the possibility doesn't have a destructible, select the other if it has one
                    possibility = actor.get();
            }
            else
                possibility = actor.get();

            // if we found a possibility of actor which is alive, return it
            if (actor::Destructible* dp = possibility->destructible(); dp != nullptr && !dp->is_dead())
                break;
        }
    }
    return possibility;
}

bool Level::is_in_fov(int x, int y)
{
    if (x < 0 || y < 0 || x >= m_width || y >= m_height)
        return false;

    if (m_map->isInFov(x, y))
        return m_tiles[x + y * m_width].explored = true;
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

void Level::render(pat::Engine* engine)
{
    // TODO clean up the colors from the level::render
    static const TCODColor darkWall(0, 0, 100);
    static const TCODColor darkGround(50, 50, 150);
    static const TCODColor lightWall(130, 110, 50);
    static const TCODColor lightGround(200, 180, 50);

    int dx = engine->get_player()->get_x() - engine->width()  / 2,
        dy = engine->get_player()->get_y() - engine->height() / 2;

    for (int x = 0; x < m_width; ++x)
    {
        for (int y = 0; y < m_height; ++y)
        {
            if (is_in_fov(x, y))
                TCODConsole::root->setCharBackground(x - dx, y - dy, is_wall(x, y) ? lightWall : lightGround);
            else if (is_explored(x, y))
                TCODConsole::root->setCharBackground(x - dx, y - dy, is_wall(x, y) ? darkWall : darkGround);
        }
    }

    auto render_ = [this, &dx, &dy](bool render_dead_ones) {
        for (const auto& actor : m_actors)
        {
            if (m_map->isInFov(actor->get_x(), actor->get_y()))
            {
                actor::Destructible* d = actor->destructible();
                if (d != nullptr && (render_dead_ones ? d->is_dead() : !d->is_dead()))
                    actor->render(dx, dy);
                else if (d == nullptr)
                    actor->render(dx, dy);
            }
        }
    };

    // render the dead ones first, then the alive ones
    render_(/* render_dead_ones */ true);
    render_(/* render_dead_ones */ false);
}

void Level::update(pat::Engine* engine)
{
    // called once per new turn
    for (const auto& actor : m_actors)
    {
        if (actor.get() != engine->get_player())
            actor->update(engine);
    }
}

void Level::enter(const std::shared_ptr<pat::Actor>& player)
{
    // the player just entered the level, put it in the middle
    // of the first room
    m_actors.emplace_back(player);
    m_actors.back()->put_at(
        m_rooms[0].x + m_rooms[0].width / 2,
        m_rooms[0].y + m_rooms[0].height / 2
    );
}

void Level::exit(const std::shared_ptr<pat::Actor>& player)
{
    auto it = std::remove_if(m_actors.begin(), m_actors.end(), [&player](const auto& actor) -> bool {
        return actor.get() == player.get();
    });
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

void Level::create_room(int x1, int y1, int x2, int y2)
{
    dig(x1, y1, x2, y2);

    m_rooms.emplace_back(
        (x2 < x1) ? x2 : x1,
        (y2 < y1) ? y2 : y1,
        (x1 > x2) ? x1 - x2 : x2 - x1,
        (y1 > y2) ? y1 - y2 : y2 - y1
    );

    // TODO make the monster generation better
    TCODRandom* rng = TCODRandom::getInstance();
    int nb_monsters = rng->getInt(0, details::max_room_monsters);

    while (nb_monsters > 0)
    {
        int x = rng->getInt(x1, x2);
        int y = rng->getInt(y1, y2);
        if (can_walk(x, y))
        {
            // create an orc
            if (rng->getInt(0, 100) < 80)
            {
                m_actors.emplace_back(std::make_shared<Actor>(x, y, 'o', "orc", TCODColor::desaturatedGreen));
                m_actors.back()->set_attacker<actor::Attacker>(3.0f);
                m_actors.back()->set_destructible<actor::details::MonsterDestructible>(10.0f, 0.0f, "dead orc");
            }
            // create a troll
            else
            {
                m_actors.emplace_back(std::make_shared<Actor>(x, y, 'T', "troll", TCODColor::darkerGreen));
                m_actors.back()->set_attacker<actor::Attacker>(4.0f);
                m_actors.back()->set_destructible<actor::details::MonsterDestructible>(16.0f, 1.0f, "troll carcass");
            }

            m_actors.back()->set_ai<actor::details::MonsterAI>();
        }
        --nb_monsters;
    }
}
