#include <Pataro/Map/Level.hpp>

#include <Pataro/Map/BSPListener.hpp>
#include <Pataro/Map/Constants.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Utils.hpp>

#include <algorithm>

using namespace pat::map;

Level::Level(int width, int height, Engine* engine, const Config::Theme& theme) :
    m_tiles(width * height, Tile(Tile::Type::Wall)),
    m_width(width), m_height(height), m_engine(engine), m_theme(theme)
{}

Tile::Type Level::tile_at(int x, int y) const
{
    if (0 <= x && x < m_width && 0 <= y && y < m_height)
        return m_tiles[x + y * m_width].type;
    return Tile::Type::Wall;
}

bool Level::can_walk(int x, int y) const
{
    if (!m_map->isWalkable(x, y))
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
            auto dist = static_cast<float>(pat::details::get_manhattan_distance(
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

void Level::render(float dt)
{
    int dx = m_engine->get_player()->get_x() - m_engine->width()  / 2,
        dy = m_engine->get_player()->get_y() - m_engine->height() / 2;

    for (unsigned screen_x = 0; screen_x < m_engine->width(); ++screen_x)
    {
        for (unsigned screen_y = 0; screen_y < m_engine->height(); ++screen_y)
        {
            int world_x = static_cast<int>(screen_x) + dx;
            int world_y = static_cast<int>(screen_y) + dy;
            TCOD_ConsoleTile& tile = m_engine->console().at(screen_x, screen_y);

            // IMPORTANT: the type index should the same (and have the same order) as the one defines under Config.hpp
            auto type_idx = static_cast<std::size_t>(m_tiles[world_x + world_y * m_width].type);
            if (type_idx <= 2)
            {
                if (is_in_fov(world_x, world_y))
                {
                    tile.ch = m_theme.colors[type_idx].repr;
                    tile.bg = m_theme.colors[type_idx].color_visible;
                }
                else if (is_explored(world_x, world_y))
                {
                    tile.ch = m_theme.colors[type_idx].repr;
                    tile.bg = m_theme.colors[type_idx].color_outside_fov;
                }
            }
        }
    }

    auto render_ = [this, &dt, &dx, &dy](bool render_dead_ones) {
        for (const auto& entity : m_entities)
        {
            if (m_map->isInFov(entity->get_x(), entity->get_y()))
            {
                component::Destructible* d = entity->destructible();
                if (d != nullptr && (render_dead_ones ? d->is_dead() : !d->is_dead()))
                    entity->render(m_engine->console(), dt, dx, dy);
                else if (d == nullptr)
                    entity->render(m_engine->console(), dt, dx, dy);
            }
        }
    };

    // render the dead ones first, then the alive ones
    render_(/* render_dead_ones */ true);
    render_(/* render_dead_ones */ false);
}

void Level::update()
{
    // called once per new turn
    for (const auto & entity : m_entities)
    {
        if (entity.get() != m_engine->get_player())
        {
            entity->gain_energy();
            if (entity->has_enough_energy())
            {
                std::unique_ptr<pat::Action> action = entity->update(m_engine);
                if (action != nullptr)
                    action->perform(m_engine);
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

std::shared_ptr<pat::Entity> Level::remove(pat::Entity* entity)
{
    auto it = std::remove_if(m_entities.begin(), m_entities.end(), [&entity](const auto& entity_) -> bool {
        return entity_.get() == entity;
    });
    auto copy = *it;
    m_entities.erase(it);
    return copy;
}

void Level::generate()
{
    m_map = std::make_unique<TCODMap>(m_width, m_height);

    // TODO: expose the parameters in the generate() methods arguments
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

    // put stairs in the last room generated
    int x = m_rooms.back().x + m_rooms.back().width / 2;
    int y = m_rooms.back().y + m_rooms.back().height / 2;

    m_tiles[x + y * m_width] = Tile(Tile::Type::Stairs);
    // FIXME this prevents the player from using FollowStairs actions because collisions m_map->setProperties(x, y, true, false);  // set the stairs as not walkable
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
        {
            m_tiles[x + y * m_width].type = Tile::Type::Ground;
            // transparent & walkable
            m_map->setProperties(x, y, true, true);
        }
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

    TCODRandom* rng = TCODRandom::getInstance();
    int nb_monsters = rng->getInt(0, details::max_room_monsters);
    int nb_items    = rng->getInt(0, details::max_room_items);

    while (nb_monsters + nb_items > 0)
    {
        int x = rng->getInt(x1, x2);
        int y = rng->getInt(y1, y2);

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
