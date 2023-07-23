#include <Pataro/Components/Inventory.hpp>

#include <Pataro/Entity.hpp>

#include <algorithm>

using namespace pat::component;

Inventory::Inventory(std::size_t size) :
    m_max_size(size)
{}

bool Inventory::add(pat::Entity* entity)
{
    // inventory full
    if (m_max_size > 0 && m_inventory.size() >= m_max_size)
        return false;

    m_inventory.push_back(*entity);
    return true;
}

void Inventory::remove(pat::Entity* entity)
{
    auto it = std::remove_if(m_inventory.begin(), m_inventory.end(), [entity](const Entity& e) -> bool {
        return entity->id() == e.id();
    });
    m_inventory.erase(it);
}

const pat::Entity& Inventory::operator[](std::size_t index) const
{
    return m_inventory[index];
}

pat::Entity* Inventory::ptr_at(std::size_t index)
{
    return &m_inventory[index];
}

std::size_t Inventory::size() const
{
    return m_inventory.size();
}

std::size_t Inventory::capacity() const
{
    return m_max_size;
}

Inventory* Inventory::clone_impl() const
{
    return new Inventory(*this);
}