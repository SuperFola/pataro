#include <Pataro/Actor.hpp>

#include <Pataro/Engine.hpp>

#include <iostream>

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

void Actor::render() const
{
    TCODConsole::root->setChar(m_x, m_y, m_ch);
    TCODConsole::root->setCharForeground(m_x, m_y, m_color);
}

void Actor::update(Engine* engine)
{
    if (m_ai)
        m_ai->update(this, engine);
}
