#ifndef PATARO_MAP_MAP_HPP
#define PATARO_MAP_MAP_HPP

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
         * @brief Render the map on the screen
         * 
         */
        void render() const;

    private:
        std::vector<map::Level> m_levels;
        // TODO add method to change current level
        std::size_t m_current = 0;
    };
}

#endif