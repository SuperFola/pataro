#include <Pataro/Entity.hpp>

#include <Pataro/Engine.hpp>

using namespace pat;

unsigned Entity::Id = 0;

Entity::Entity(int x, int y, int ch, const std::string& name, const TCODColor& color) :
    m_id(Entity::Id++), m_x(x), m_y(y), m_ch(ch), m_name(name), m_color(color)
{}


Entity::Entity(const Entity& other) :
    m_id(other.m_id),
    m_x(other.m_x), m_y(other.m_y),
    m_ch(other.m_ch),
    m_name(other.m_name),
    m_color(other.m_color),
    m_blocks(other.m_blocks),
    m_attacker(other.m_attacker ? other.m_attacker->clone() : nullptr),
    m_destructible(other.m_destructible ? other.m_destructible->clone() : nullptr),
    m_ai(other.m_ai ? other.m_ai->clone() : nullptr),
    m_container(other.m_container ? other.m_container->clone() : nullptr),
    m_use(other.m_use ? other.m_use->clone() : nullptr)
{}

Entity& Entity::operator=(const Entity& other)
{
    m_id = other.m_id;
    m_x = other.m_x;
    m_y = other.m_y;
    m_ch = other.m_ch;
    m_name = other.m_name;
    m_color = other.m_color;
    m_blocks = other.m_blocks;
    m_attacker = other.m_attacker ? other.m_attacker->clone() : nullptr;
    m_destructible = other.m_destructible ? other.m_destructible->clone() : nullptr;
    m_ai = other.m_ai ? other.m_ai->clone() : nullptr;
    m_use = other.m_use ? other.m_use->clone() : nullptr;
    m_container = other.m_container ? other.m_container->clone() : nullptr;

    return *this;
}

void Entity::morph_into(int ch, const TCODColor& color)
{
    m_ch = ch;
    m_color = color;
}

void Entity::render(int dx, int dy) const
{
    if (m_animation)
    {
        float dt = TCODSystem::getLastFrameLength();
        m_animation->update(dt);
        if (m_animation->is_finished())
            m_animation.reset(nullptr);
    }

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

void Entity::set_animation(const Animation& anim)
{
    m_animation = std::make_unique<Animation>(anim);
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