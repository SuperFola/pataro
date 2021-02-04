#include <game/Actor.hpp>

Actor::Actor(int x, int y, int ch, const TCODColor& color) :
    m_x(x), m_y(y), m_ch(ch), m_color(color)
{}

void Actor::render() const
{}