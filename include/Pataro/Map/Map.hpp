#ifndef PATARO_MAP_MAP_HPP
#define PATARO_MAP_MAP_HPP

#include <Pataro/Map/Tile.hpp>

#include <vector>

namespace pat
{
    class Map
    {
    public:
        /**
         * @brief Construct a new Map object
         * 
         * @param width 
         * @param height 
         */
        Map(unsigned width, unsigned height);

        /**
         * @brief Check if an object at (x, y) is a wall
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
        /**
         * @brief Put a wall at (x, y)
         * 
         * @param x 
         * @param y 
         */
        void set_wall(unsigned x, unsigned y);

        std::vector<map::Tile> m_tiles;
        unsigned m_width;
        unsigned m_height;
    };
}

#endif