#ifndef PATARO_MAP_HPP
#define PATARO_MAP_HPP

#include <Pataro/Map/Level.hpp>

#include <vector>

namespace pat
{
    class Map
    {
    public:
        /**
         * @brief Construct a new Map object
         * 
         * @param depth number of levels to generate
         */
        Map(std::size_t depth);

        /**
         * @brief Check if a tile at (x, y) is a wall
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool is_wall(int x, int y) const;

        /**
         * @brief check if an actor can walk on a given tile
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool can_walk(int x, int y) const;

        /**
         * @brief Compute the player field of view
         * 
         * @param x player position
         * @param y player position
         * @param fov_radius in tiles
         */
        void compute_fov(int x, int y, int fov_radius);

        /**
         * @brief Render the map on the screen
         * 
         */
        void render();

        /**
         * @brief get the current level
         * 
         * @return const map::Level& 
         */
        const map::Level& current_level() const;

    private:
        std::vector<map::Level> m_levels;
        // TODO add method to change current level
        std::size_t m_current = 0;
    };
}

#endif