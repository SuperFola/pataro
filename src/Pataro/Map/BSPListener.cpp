#include <Pataro/Map/BSPListener.hpp>

#include <Pataro/Map/Map.hpp>
#include <Pataro/Map/Constants.hpp>

using namespace pat::map::details;

BSPListener::BSPListener(Map* map) :
    m_map(map), m_room_nb(0)
{}

bool BSPListener::visitNode(TCODBsp* node, void* userData)
{
    if (node->isLeaf())
    {
        TCDORandom* rng = TCODRandom::getInstance();

        int w = rng->getInt(room_min_w, node->w - 2);
        int h = rng->getInt(room_min_h, node->h - 2);
        int x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
        int y = rng->getInt(node->y + 1, node->y + node->h - h - 1);

        m_map->dig(x, y, w, h);

        // dig corridors
        if (m_room_nb != 0)
        {
            m_map->dig(m_lastx, m_lasty, x + w / 2, m_lasty);
            m_map->dig(x + w / 2, m_lasty, x + w / 2, y + h / 2);
        }

        m_lastx = x + w / 2;
        m_lasty = y + h / 2;
        m_room_nb++;

        return true;
    }
}