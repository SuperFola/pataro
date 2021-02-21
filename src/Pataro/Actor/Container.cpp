#include <Pataro/Actor/Container.hpp>

#include <Pataro/Actor.hpp>

using namespace pat::actor;

Container::Container(std::size_t size) :
    m_max_size(size)
{}

bool Container::add(const pat::Actor& actor)
{
    // inventory full
    if (m_max_size > 0 && m_inventory.size() >= m_max_size)
        return false;

    m_inventory.push_back(actor);
    return true;
}