#include <Pataro/Actor/Container.hpp>

#include <Pataro/Actor.hpp>

#include <algorithm>

using namespace pat::actor;

Container::Container(std::size_t size) :
    m_max_size(size)
{}

bool Container::add(pat::Actor* actor)
{
    // inventory full
    if (m_max_size > 0 && m_inventory.size() >= m_max_size)
        return false;

    m_inventory.emplace_back(*actor);
    return true;
}

void Container::remove(pat::Actor* actor)
{
    auto it = std::remove_if(m_inventory.begin(), m_inventory.end(), [&actor](const pat::Actor& actor_) -> bool {
        return actor_.id() == actor->id();
    });
}

Container* Container::clone_impl() const
{
    return new Container(*this);
}