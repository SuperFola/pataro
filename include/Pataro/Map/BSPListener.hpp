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
         * @param with_entities parameter to forward to lever->create_room()
         */
        BSPListener(Level* level, bool with_entities);

        bool visitNode(TCODBsp* node, void* userData) override;

    private:
        Level* m_level;
        int m_room_nb;
        int m_lastx;
        int m_lasty;
        bool m_with_entities;
    };
}

#endif
