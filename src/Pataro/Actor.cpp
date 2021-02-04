#include <Pataro/Actor.hpp>

using namespace pat;

Actor::Actor(int x, int y, int ch, const TCODColor& color) :
    m_x(x), m_y(y), m_ch(ch), m_color(color)
{}

void Actor::render() const
{
    TCODConsole::root->setChar(m_x, m_y, m_ch);
    TCODConsole::root->setCharForeground(m_x, m_y, m_color);
}

void Actor::move(int dx, int dy)
{
    m_x += dx;
    m_y += dy;
}