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

void Use::drop(pat::Entity* source, pat::Entity* owner, pat::Engine* engine) const
{
    // we can not drop a used object
    if (m_destroyed)
        return;

    if (Inventory* c = owner->inventory(); c != nullptr)
    {
        source->put_at(owner->get_x(), owner->get_y());
        engine->get_map()->current_level().add(source);
        c->remove(source);
    }
}

void Use::remove_from_inventory(pat::Entity* owner, pat::Entity* source)
{
    owner->inventory()->remove(source);
}