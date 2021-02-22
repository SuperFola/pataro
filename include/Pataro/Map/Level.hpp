#ifndef PATARO_MAP_LEVEL_HPP
#define PATARO_MAP_LEVEL_HPP

#include <Pataro/Map/Tile.hpp>
#include <Pataro/Map/Room.hpp>
#include <Pataro/Entity.hpp>

#include <libtcod.hpp>

#include <vector>
#include <memory>

namespace pat
{
    class Map;
    class Engine;
}

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
         * @brief check if an Entity can walk on a given tile
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool can_walk(int x, int y) const;

        /**
         * @brief Tries to get an Entity at x, y
         * 
         * @param x 
         * @param y 
         * @return Entity* nullptr if no Entity was found
         */
        Entity* get_entity(int x, int y) const;

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
         * @brief Render the level on screen as well as its Entities
         * 
         * @param engine 
         */
        void render(Engine* engine);

        /**
         * @brief Update the levels (Entities and stuff)
         * 
         * @param engine 
         */
        void update(Engine* engine);

        /**
         * @brief Add a copy of the player to the level
         * 
         * @param player 
         */
        void enter(const std::shared_ptr<Entity>& player);

        /**
         * @brief Remove an Entity from the level
         * 
         * @param Entity 
         */
        void remove(Entity* Entity);

        inline const std::vector<std::shared_ptr<Entity>>& get_entities() { return m_entities; }

        friend class details::BSPListener;
        friend class pat::Map;

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
         * @param x1 
         * @param y1 
         * @param x2 
         * @param y2 
         */
        void create_room(int x1, int y1, int x2, int y2);

        std::vector<details::Tile> m_tiles;
        std::unique_ptr<TCODMap> m_map;
        std::vector<details::Room> m_rooms;
        std::vector<std::shared_ptr<Entity>> m_entities;
        int m_width;
        int m_height;
    };
}

#endif