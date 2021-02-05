#ifndef PATARO_MAP_BSPLISTENER_HPP
#define PATARO_MAP_BSPLISTENER_HPP

#include <libtcod.hpp>

namespace pat::map
{
    class Map;
}

namespace pat::map::details
{
    class BSPListener : ITCODBspCallback
    {
    public:
        /**
         * @brief Construct a new BSPListener object
         * 
         * @param map 
         */
        BSPListener(Map* map);

        bool visitNode(TCODBsp* node, void *userData);

    private:
        Map* m_map;
        int m_room_nb;
        int m_lastx;
        int m_lasty;
    };
}

#endif