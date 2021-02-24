#include <Pataro/Components/Container.hpp>

#include <Pataro/Entity.hpp>

#include <algorithm>

using namespace pat::component;

Container::Container(std::size_t size) :
    m_max_size(size)
{}

bool Container::add(pat::Entity* actor)
{
    // inventory full
    if (m_max_size > 0 && m_inventory.size() >= m_max_size)
        return false;

    // FIXME
    // m_inventory.emplace_back(*actor);
    return true;
}

void Container::remove(pat::Entity* actor)
{
    // FIXME
}