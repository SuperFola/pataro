#include <Pataro/Entity.hpp>

#include <Pataro/Engine.hpp>

using namespace pat;

Entity::Entity(int x, int y, int ch, const std::string& name, const TCODColor& color) :
    m_id(Entity::Id++), m_x(x), m_y(y), m_ch(ch), m_name(name), m_color(color)
{}

void Entity::morph_into(int ch, const std::string& name, const TCODColor& color)
{
    m_ch = ch;
    m_name = name;
    m_color = color;
}

void Entity::render(int dx, int dy) const
{
    TCODConsole::root->setChar(m_x - dx, m_y - dy, m_ch);
    TCODConsole::root->setCharForeground(m_x - dx, m_y - dy, m_color);
}

std::unique_ptr<Action> Entity::update(Engine* engine)
{
    if (m_ai)
        return m_ai->update(this, engine);
    return nullptr;
}

void Entity::gain_energy()
{
    m_energy += m_speed;
}

bool Entity::has_enough_energy() const
{
    return m_energy >= 1.f;
}

void Entity::put_at(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Entity::move(int dx, int dy)
{
    m_x += dx;
    m_y += dy;
}
