#ifndef PATARO_MAP_LEVEL_HPP
#define PATARO_MAP_LEVEL_HPP

#include <Pataro/Map/Tile.hpp>

#include <vector>

namespace pat::map
{
    class Level
    {
    public:
        /**
         * @brief Construct a new Level object
         * 
         * @param width 
         * @param height 
         */
        Level(int width, int height);

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
         * @brief Render the level on screen
         * 
         */
        void render() const;

    private:
        /**
         * @brief Dig a rectangular zone in the level
         * 
         * @param x 
         * @param y 
         * @param w the width of the zone
         * @param h the height of the zone
         */
        void dig(int x, int y, int w, int h);

        std::vector<map::Tile> m_tiles;
        int m_width;
        int m_height;
    };
}

#endif