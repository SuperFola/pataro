#include <Pataro/Map/Level.hpp>

#include <Pataro/Map/BSPListener.hpp>
#include <Pataro/Map/Constants.hpp>
#include <Pataro/Map.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Utils.hpp>

#include <algorithm>

using namespace pat::map;

Level::Level(int width, int height, TCODRandom* rng) :
    m_tiles(width * height, details::Tile()),
    m_width(width),
    m_height(height),
    m_rng(rng)
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

    for (const auto& entity : m_entities)
    {
        if (entity->get_x() == x && entity->get_y() == y && entity->is_blocking())
            return false;
    }
    return true;
}

pat::Entity* Level::get_entity(int x, int y) const
{
    pat::Entity* possibility = nullptr;

    for (const auto& entity : m_entities)
    {
        if (entity->get_x() == x && entity->get_y() == y)
        {
            if (possibility != nullptr)
            {
                component::Destructible* d = entity->destructible();
                component::Destructible* dp = possibility->destructible();

                // if there is another possibility which is alive, discard current one

                if (d != nullptr && dp != nullptr && dp->is_dead() && !d->is_dead())  // the new one is alive, the old one is dead, keep the alive one
                    possibility = entity.get();
                else if (d != nullptr && dp != nullptr && dp->is_dead() && d->is_dead())  // both dead, keep new one because why not
                    possibility = entity.get();
                else if (dp == nullptr && d != nullptr)  // if the possibility doesn't have a destructible, select the other if it has one
                    possibility = entity.get();
            }
            else
                possibility = entity.get();

            // if we found a possibility of entity which is alive, return it
            if (component::Destructible* dp = possibility->destructible(); dp != nullptr && !dp->is_dead())
                break;
        }
    }
    return possibility;
}

pat::Entity* Level::get_closest_monster(pat::Entity* from, float range) const
{
    Entity* closest = nullptr;
    float best_distance = 1e6f;

    for (const auto& entity : m_entities)
    {
        if (component::Destructible* d = entity->destructible(); entity.get() != from
            && d != nullptr && !d->is_dead())
        {
            float dist = static_cast<float>(pat::details::get_manhattan_distance(
                from->get_x(), from->get_y(),
                entity->get_x(), entity->get_y()
            ));

            if (dist < best_distance && (dist <= range || range == 0.f))
            {
                best_distance = dist;
                closest = entity.get();
            }
        }
    }

    return closest;
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
        for (const auto& entity : m_entities)
        {
            if (m_map->isInFov(entity->get_x(), entity->get_y()))
            {
                component::Destructible* d = entity->destructible();
                if (d != nullptr && (render_dead_ones ? d->is_dead() : !d->is_dead()))
                    entity->render(dx, dy);
                else if (d == nullptr)
                    entity->render(dx, dy);
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
    for (std::size_t i = 0; i < m_entities.size(); ++i)
    {
        if (m_entities[i].get() != engine->get_player())
        {
            m_entities[i]->gain_energy();
            if (m_entities[i]->has_enough_energy())
            {
                std::unique_ptr<pat::Action> action = m_entities[i]->update(engine);
                if (action != nullptr)
                    action->perform(engine);
            }
        }
    }
}

void Level::enter(const std::shared_ptr<pat::Entity>& player)
{
    // the player just entered the level, put it in the middle
    // of the first room
    m_entities.emplace_back(player);
    m_entities.back()->put_at(
        m_rooms[0].x + m_rooms[0].width / 2,
        m_rooms[0].y + m_rooms[0].height / 2
    );
}

void Level::add(pat::Entity* entity)
{
    m_entities.insert(
        m_entities.begin(),
        std::make_shared<Entity>(*entity)
    );
}

void Level::remove(pat::Entity* entity)
{
    auto it = std::remove_if(m_entities.begin(), m_entities.end(), [&entity](const auto& entity_) -> bool {
        return entity_.get() == entity;
    });
    m_entities.erase(it);
}

void Level::generate(bool with_entities)
{
    m_map = std::make_unique<TCODMap>(m_width, m_height);

    // generate the level
    TCODBsp bsp(0, 0, m_width, m_height);
    bsp.splitRecursive(
        // our own randomizer
        m_rng,
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
    details::BSPListener listener(this, with_entities);
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

void Level::create_room(int x1, int y1, int x2, int y2, bool with_entities)
{
    dig(x1, y1, x2, y2);

    m_rooms.emplace_back(
        (x2 < x1) ? x2 : x1,
        (y2 < y1) ? y2 : y1,
        (x1 > x2) ? x1 - x2 : x2 - x1,
        (y1 > y2) ? y1 - y2 : y2 - y1
    );

    if (with_entities)
    {
        int nb_monsters = m_rng->getInt(0, details::max_room_monsters);
        int nb_items    = m_rng->getInt(0, details::max_room_items);

        while (nb_monsters + nb_items > 0)
        {
            int x = m_rng->getInt(x1, x2);
            int y = m_rng->getInt(y1, y2);

            if (can_walk(x, y))
            {
                if (nb_monsters > 0)
                    m_entities.emplace_back(m_factory.get_random_monster(x, y));
                else if (nb_items > 0)
                    m_entities.emplace_back(m_factory.get_random_item(x, y));
            }

            if (nb_monsters > 0)
                --nb_monsters;
            else if (nb_items > 0)
                --nb_items;
        }
    }
}
