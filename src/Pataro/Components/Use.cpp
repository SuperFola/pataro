#include <Pataro/Components/Use.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::component;

std::unique_ptr<pat::Action> Use::perform(pat::Entity* source, pat::Engine* engine)
{
    // can not use, the component is destroyed
    if (m_destroyed)
        return nullptr;
    return use(source, engine);
}

bool Use::is_destroyed() const
{
    return m_destroyed;
}

void Use::mark_destroyed()
{
    m_destroyed = true;
}