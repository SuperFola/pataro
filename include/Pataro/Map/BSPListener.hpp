#ifndef PATARO_MAP_BSPLISTENER_HPP
#define PATARO_MAP_BSPLISTENER_HPP

#include <libtcod.hpp>

namespace pat::map
{
    class Level;
}

namespace pat::map::details
{
    class BSPListener : public ITCODBspCallback
    {
    public:
        /**
         * @brief Construct a new BSPListener object
         * 
         * @param level 
         */
        BSPListener(Level* level);

        bool visitNode(TCODBsp* node, void *userData);

    private:
        Level* m_level;
        int m_room_nb;
        int m_lastx;
        int m_lasty;
    };
}

#endif