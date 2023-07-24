#include <Pataro/Map.hpp>

#include <Pataro/Engine.hpp>

#include <libtcod.hpp>

using namespace pat;

Map::Map(unsigned width, unsigned height, std::size_t depth, Engine* engine, const Config::Theme& theme) :
    m_current(0)
{
    // create levels
    for (std::size_t i = 0; i < depth; ++i)
    {
        m_levels.emplace_back(width, height, engine, theme);
        m_levels.back().generate();  // TODO: tune the generation settings for each level
    }
}

map::Tile::Type Map::tile_at(int x, int y) const
{
    return m_levels[m_current].tile_at(x, y);
}

bool Map::can_walk(int x, int y) const
{
    // bounds are already checked underneath
    return m_levels[m_current].can_walk(x, y);
}

pat::Entity* Map::get_entity(int x, int y) const
{
    return m_levels[m_current].get_entity(x, y);
}

pat::Entity* Map::get_closest_monster(pat::Entity* from, float range) const
{
    return m_levels[m_current].get_closest_monster(from, range);
}

void Map::compute_fov(int x, int y, int fov_radius)
{
    m_levels[m_current].compute_fov(x, y, fov_radius);
}

bool Map::is_in_fov(int x, int y)
{
    return m_levels[m_current].is_in_fov(x, y);
}

void Map::render(float dt)
{
    m_levels[m_current].render(dt);
}

void Map::update()
{
    m_levels[m_current].update();
}

bool Map::move_upstairs(Entity* player)
{
    if (can_go_upstairs())
    {
        auto player_ptr = current_level().remove(player);
        --m_current;
        current_level().enter(player_ptr);
        return true;
    }
    return false;
}

bool Map::move_downstairs(Entity* player)
{
    if (can_go_downstairs())
    {
        auto player_ptr = current_level().remove(player);
        ++m_current;
        current_level().enter(player_ptr);
        return true;
    }
    return false;
}
