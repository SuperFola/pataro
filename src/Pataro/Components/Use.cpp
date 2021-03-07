#include <Pataro/Components/Use.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::component;

std::unique_ptr<pat::Action> Use::perform(pat::Entity* source, pat::Entity* owner, pat::Engine* engine)
{
    // can not use, the component is destroyed
    if (m_destroyed)
        return nullptr;
    return use(source, owner, engine);
}

void Use::remove_from_container(pat::Entity* owner, pat::Entity* source)
{
    owner->container()->remove(source);
}