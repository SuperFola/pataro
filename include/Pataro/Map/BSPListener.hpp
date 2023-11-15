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
        explicit BSPListener(Level* level);

        bool visitNode(TCODBsp* node, void* userData) override;

    private:
        Level* m_level;
        int m_room_nb;
        int m_lastx;  // TODO find a better name
        int m_lasty;  // TODO find a better name
    };
}

#endif
