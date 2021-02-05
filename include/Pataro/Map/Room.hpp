#ifndef PATARO_MAP_ROOM_HPP
#define PATARO_MAP_ROOM_HPP

#include <Pataro/Actor.hpp>

#include <optional>

namespace pat::map::details
{
    class Room
    {
    public:
        /**
         * @brief Construct a new Room object
         * 
         * @param x 
         * @param y 
         * @param w 
         * @param h 
         */
        Room(int x, int y, int w, int h);

        /**
         * @brief Get the actor object
         * 
         * @return std::optional<Actor> 
         */
        std::optional<pat::Actor> get_actor() const;

    private:
        int m_x, m_y, m_width, m_height;
        std::optional<Actor> m_actor = {};
    };
}

#endif