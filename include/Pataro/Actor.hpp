#ifndef PATARO_ACTOR_HPP
#define PATARO_ACTOR_HPP

#include <libtcod.hpp>

#include <string>

namespace pat
{
    class Map;

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

        inline int get_x() const
        {
            return m_x;
        }

        inline int get_y() const
        {
            return m_y;
        }

        void update();

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
        int m_x;
        int m_y;
        int m_ch;
        std::string m_name;
        TCODColor m_color;
    };
}

#endif