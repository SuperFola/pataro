#ifndef PATARO_ACTOR_HPP
#define PATARO_ACTOR_HPP

#include <Pataro/Actor/AI.hpp>
#include <Pataro/Actor/Attacker.hpp>
#include <Pataro/Actor/Destructible.hpp>

#include <libtcod.hpp>

#include <string>

namespace pat
{
    class Map;

    /**
     * @brief An actor class representing items, traps, doors, monsters, players...
     * @details It uses composition to represent all of those kind of actors.
     * 
     */
    class Actor
    {
    public:
        /**
         * @brief Construct a new Actor object
         * 
         * @param x position on X axis
         * @param y position on Y axis
         * @param ch ascii code representing the character
         * @param name the name of the actor
         * @param color the color for the actor
        */
        Actor(int x, int y, int ch, const std::string& name, const TCODColor& color);

        /**
         * @brief display the actor on screen
         * 
        */
        void render() const;

        inline int get_x() const { return m_x; }
        inline int get_y() const { return m_y; }

        inline const std::string& get_name() const { return m_name; }

        inline bool is_blocking() const { return m_blocks; }

        /**
         * @brief Update the actor
         * 
         */
        void update();

        /**
         * @brief Move the actor / attack if an entity is blocking the way
         * 
         * @param dx 
         * @param dy 
         * @param map 
         * @return true we were able to move
         * @return false we were blocked by a wall / an ennemy
         */
        bool move_or_attack(int dx, int dy, Map* map);

        /**
         * @brief Move the actor
         * 
         * @param dx 
         * @param dy 
         * @param map a pointer to the map, to check for collisions
         * @return true if we were able to move
         * @return false otherwise
         */
        bool move(int dx, int dy, Map* map);

    private:
        int m_x, m_y;
        int m_ch;
        std::string m_name;
        TCODColor m_color;

        bool m_blocks = true;  ///< Can we walk on this actor?
        std::unique_ptr<details::Attacker> m_attacker = nullptr;  ///< For actors that deal damages
        std::unique_ptr<details::Destructible> m_destructible = nullptr;  ///< For destructible actors
        std::unique_ptr<details::AI> m_ai = nullptr;  ///< For self updating actors
    };
}

#endif
