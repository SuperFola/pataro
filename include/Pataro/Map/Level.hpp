#ifndef PATARO_MAP_LEVEL_HPP
#define PATARO_MAP_LEVEL_HPP

#include <Pataro/Map/Tile.hpp>
#include <Pataro/Map/Room.hpp>
#include <Pataro/Actor.hpp>

#include <libtcod.hpp>

#include <vector>
#include <memory>

namespace pat::map
{
    namespace details
    {
        class BSPListener;
    }

    /**
     * @brief Handles a single level/floor of a map
     * @details Each level holds it's own representation of the player
     *          which is retrieved by the engine through the map to
     *          interact with it.
     * 
     */
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
         * @brief check if an actor can walk on a given tile
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool can_walk(int x, int y) const;

        /**
         * @brief Tries to get an actor at x, y
         * 
         * @param x 
         * @param y 
         * @return Actor* nullptr if no actor was found
         */
        Actor* get_actor(int x, int y) const;

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
         * @brief Check if a tile has been explored
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool is_explored(int x, int y) const;

        /**
         * @brief Compute the player field of view
         * 
         * @param x player position
         * @param y player position
         * @param fov_radius in tiles
         */
        void compute_fov(int x, int y, int fov_radius);

        /**
         * @brief Render the level on screen as well as its actors
         * 
         */
        void render();

        /**
         * @brief Update the levels (actors and stuff)
         * 
         */
        void update();

        /**
         * @brief Add a copy of the player to the level
         * 
         * @param player 
         */
        void enter(const std::shared_ptr<Actor>& player);

        /**
         * @brief Remove the player from the level
         * @details Avoid dealing with more than one player when we come back
         * 
         * @param player 
         */
        void exit(const std::shared_ptr<Actor>& player);

    private:
        /**
         * @brief Generate the world
         * 
         */
        void generate();

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
        friend class pat::Map;

        std::vector<details::Tile> m_tiles;
        std::unique_ptr<TCODMap> m_map;
        std::vector<details::Room> m_rooms;
        std::vector<std::shared_ptr<Actor>> m_actors;
        int m_width;
        int m_height;
    };
}

#endif