#include <Pataro/Components/Container.hpp>

#include <Pataro/Entity.hpp>

#include <algorithm>

using namespace pat::component;

Container::Container(std::size_t size) :
    m_max_size(size)
{}

bool Container::add(pat::Entity* entity)
{
    // inventory full
    if (m_max_size > 0 && m_inventory.size() >= m_max_size)
        return false;

    m_inventory.push_back(*entity);
    return true;
}

void Container::remove(pat::Entity* entity)
{
    auto it = std::remove_if(m_inventory.begin(), m_inventory.end(), [entity](const Entity& e) -> bool {
        return entity->id() == e.id();
    });
}

Container* Container::clone_impl() const
{
    return new Container(*this);
}