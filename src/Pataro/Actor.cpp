#include <Pataro/Actor.hpp>

#include <Pataro/Engine.hpp>

using namespace pat;

Actor::Actor(int x, int y, int ch, const std::string& name, const TCODColor& color) :
    m_x(x), m_y(y), m_ch(ch), m_name(name), m_color(color)
{
    m_id = reinterpret_cast<unsigned long long>(this);
}

Actor::Actor(const Actor& actor) :
    m_x(actor.m_x), m_y(actor.m_y),
    m_ch(actor.m_ch),
    m_name(actor.m_name),
    m_color(actor.m_color),
    m_id(actor.m_id),
    m_blocks(actor.m_blocks),
    m_attacker(actor.m_attacker ? actor.m_attacker->clone() : nullptr),
    m_destructible(actor.m_destructible ? actor.m_destructible->clone() : nullptr),
    m_ai(actor.m_ai ? actor.m_ai->clone() : nullptr),
    m_pickable(actor.m_pickable ? actor.m_pickable->clone() : nullptr),
    m_container(actor.m_container ? actor.m_container->clone() : nullptr)
{}

Actor& Actor::operator=(const Actor& actor)
{
    m_x = actor.m_x;
    m_y = actor.m_y;
    m_ch = actor.m_ch;
    m_name = actor.m_name;
    m_color = actor.m_color;
    m_id = actor.m_id;
    m_blocks = actor.m_blocks;
    m_attacker = actor.m_attacker ? actor.m_attacker->clone() : nullptr;
    m_destructible = actor.m_destructible ? actor.m_destructible->clone() : nullptr;
    m_ai = actor.m_ai ? actor.m_ai->clone() : nullptr;
    m_pickable = actor.m_pickable ? actor.m_pickable->clone() : nullptr;
    m_container = actor.m_container ? actor.m_container->clone() : nullptr;

    return *this;
}

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
