#ifndef INCLUDE_PATARO_MAP_HPP
#define INCLUDE_PATARO_MAP_HPP

#include <Pataro/Config.hpp>
#include <Pataro/Map/Tile.hpp>
#include <Pataro/Map/Level.hpp>

#include <vector>

namespace pat
{
    class Entity;
    class Engine;

    class Map
    {
    public:
        /**
         * @brief Construct a new Map object
         * 
         * @param width 
         * @param height 
         * @param depth number of levels to generate
         * @param engine managed pointer to the engine
         * @param theme colors and configuration for the level
         */
        Map(unsigned width, unsigned height, std::size_t depth, Engine* engine, const Config::Theme& theme);

        /**
         * @brief Returns the type of tile at a given position. Handles bounds checking
         * 
         * @param x 
         * @param y 
         * @return Tile::Type 
         */
        [[nodiscard]] map::Tile::Type tile_at(int x, int y) const;

        /**
         * @brief check if an entity can walk on a given tile
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        [[nodiscard]] bool can_walk(int x, int y) const;

        /**
         * @brief Tries to get an entity at x, y
         * 
         * @param x 
         * @param y 
         * @return Entity* nullptr if no entity was found
         */
        [[nodiscard]] Entity* get_entity(int x, int y) const;

        /**
         * @brief Returns the closest monster to a given entity in a given range
         * 
         * @param from 
         * @param range 
         * @return Entity* 
         */
        [[nodiscard]] Entity* get_closest_monster(Entity* from, float range) const;

        /**
         * @brief Compute the player field of view
         * 
         * @param x player position
         * @param y player position
         * @param fov_radius in tiles
         */
        void compute_fov(int x, int y, int fov_radius);

        /**
         * @brief Check if a tile is in the field of view
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool is_in_fov(int x, int y);

        /**
         * @brief Render the map on the screen
         * 
         * @param dt delta time
         */
        void render(float dt);

        /**
         * @brief Update the current level
         * 
         */
        void update();

        /**
         * @brief get the current level
         * 
         * @return const map::Level& 
         */
        inline map::Level& current_level() { return m_levels[m_current]; }

        [[nodiscard]] inline std::size_t floor() const { return m_current; }
        [[nodiscard]] inline bool is_bottom_floor() const { return m_current + 1 == m_levels.size(); }

        [[nodiscard]] inline bool can_go_upstairs() const { return m_current > 0; }
        [[nodiscard]] inline bool can_go_downstairs() const { return m_current + 1 < m_levels.size(); }

        bool move_upstairs(Entity* player);
        bool move_downstairs(Entity* player);

    private:
        std::vector<map::Level> m_levels;
        std::size_t m_current;
    };
}

#endif
