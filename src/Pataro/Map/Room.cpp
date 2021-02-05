#include <Pataro/Map/Room.hpp>

#include <libtcod.hpp>

using namespace pat;
using namespace pat::map::details;

Room::Room(int x, int y, int w, int h) :
    m_x(x), m_y(y), m_width(w), m_height(h)
{
    TCODRandom* rng = TCODRandom::getInstance();
    if (rng->getInt(0, 3) == 0)
        m_actor = Actor(x + w / 2, y + h / 2, '@', TCODColor::yellow);
}

std::optional<Actor> Room::get_actor() const
{
    return m_actor;
}