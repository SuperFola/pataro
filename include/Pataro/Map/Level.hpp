#ifndef PATARO_MAP_LEVEL_HPP
#define PATARO_MAP_LEVEL_HPP

#include <Pataro/Map/Tile.hpp>
#include <Pataro/Map/Room.hpp>

#include <vector>

namespace pat::map
{
    namespace details
    {
        class BSPListener;
    }

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
         * @brief Render the level on screen as well as its actors
         * 
         */
        void render() const;

        /**
         * @brief Get the first room object
         * 
         * @return const details::Room& 
         */
        const details::Room& get_first_room() const;

    private:
        /**
         * @brief Dig a rectangular zone between (x1, y1) and (x2, y2)
         * 
         * @param x1 
         * @param y1 
         * @param x2 
         * @param y2 
         */
        void dig(int x1, int y1, int x2, int y2);

        /**
         * @brief Dig a rectangular zone between (x1, y1) and (x2, y2) and register a room
         * 
         * @param first_room
         * @param x1 
         * @param y1 
         * @param x2 
         * @param y2 
         */
        void create_room(bool first_room, int x1, int y1, int x2, int y2);

        friend class details::BSPListener;

        std::vector<details::Tile> m_tiles;
        std::vector<details::Room> m_rooms;
        int m_width;
        int m_height;
    };
}

#endif