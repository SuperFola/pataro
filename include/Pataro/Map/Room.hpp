#ifndef PATARO_MAP_ROOM_HPP
#define PATARO_MAP_ROOM_HPP

namespace pat::map::details
{
    struct Room
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
         * @brief check if the room has an actor
         * 
         * @return bool 
         */
        bool has_actor() const;

        const int x, y, width, height;

    private:
        bool m_has_actor = false;
    };
}

#endif