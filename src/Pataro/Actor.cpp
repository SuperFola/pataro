#include <Pataro/Actor.hpp>

#include <Pataro/Map.hpp>

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

void Actor::update(Map* map_ptr)
{
    if (m_ai)
        m_ai->update(this, map_ptr);
}

bool Actor::move_or_attack(int dx, int dy, Map* map)
{
    if (map->is_wall(m_x + dx, m_y + dy))
        return false;

    if (Actor* a = map->get_actor(m_x + dx, m_y + dy); a != nullptr)
    {
        std::cout << "The " << a->get_name() << " laugh at your puny efforts to attack it\n";
        return false;
    }

    m_x += dx;
    m_y += dy;

    return true;
}

bool Actor::move(int dx, int dy, Map* map)
{
    if (map->can_walk(m_x + dx, m_y + dy))
    {
        m_x += dx;
        m_y += dy;
        return true;
    }
    return false;
}