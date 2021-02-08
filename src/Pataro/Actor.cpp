#include <Pataro/Actor.hpp>

#include <Pataro/Engine.hpp>

using namespace pat;

Actor::Actor(int x, int y, int ch, const std::string& name, const TCODColor& color) :
    m_x(x), m_y(y), m_ch(ch), m_name(name), m_color(color)
{}

void Actor::morph_into(int ch, const std::string& name, const TCODColor& color)
{
    m_ch = ch;
    m_name = name;
    m_color = color;
}

void Actor::render(int dx, int dy) const
{
    TCODConsole::root->setChar(m_x - dx, m_y - dy, m_ch);
    TCODConsole::root->setCharForeground(m_x - dx, m_y - dy, m_color);
}

void Actor::update(Engine* engine)
{
    if (m_ai)
        m_ai->update(this, engine);
}
