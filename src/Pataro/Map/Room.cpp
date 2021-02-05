#include <Pataro/Map/Room.hpp>

#include <libtcod.hpp>

using namespace pat;
using namespace pat::map::details;

Room::Room(int x_, int y_, int w, int h) :
    x(x_), y(y_), width(w), height(h)
{
    TCODRandom* rng = TCODRandom::getInstance();
    if (rng->getInt(0, 3) == 0)
        m_has_actor = true;
}

bool Room::has_actor() const
{
    return m_has_actor;
}