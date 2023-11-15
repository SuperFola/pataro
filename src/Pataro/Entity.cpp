#include <Pataro/Entity.hpp>

#include <Pataro/Engine.hpp>
#include <utility>

using namespace pat;

unsigned Entity::Id = 0;

Entity::Entity(int x, int y, int ch, std::string name, const tcod::ColorRGB& color) :
    m_id(Entity::Id++), m_x(x), m_y(y), m_ch(ch), m_name(std::move(name)), m_color(color)
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
    m_inventory(other.m_inventory ? other.m_inventory->clone() : nullptr),
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
    m_inventory = other.m_inventory ? other.m_inventory->clone() : nullptr;

    return *this;
}

void Entity::morph_into(int ch, const tcod::ColorRGB& color)
{
    m_ch = ch;
    m_color = color;
}

void Entity::render(tcod::Console& console, float dt, int dx, int dy) const
{
    if (m_animation)
    {
        m_animation->update(dt);
        if (m_animation->is_finished())
            m_animation.reset(nullptr);
    }

    console.at(m_x - dx, m_y - dy).ch = m_ch;
    console.at(m_x - dx, m_y - dy).fg = m_color;
}

std::unique_ptr<Action> Entity::update(Engine* engine)
{
    if (m_ai)
    {
        m_energy -= m_speed;  // decrease energy so that the entity doesn't have infinite energy
        return m_ai->update(this, engine);
    }
    return nullptr;
}

void Entity::gain_energy()
{
    // TODO change the type of energy to something better than floats because imprecisions?
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
