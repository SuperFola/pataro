#include <Pataro/Actor/Pickable.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Actor/Container.hpp>

using namespace pat::actor;

bool Pickable::pick(pat::Actor* owner, pat::Actor* wearer, pat::Engine* engine)
{
    if (Container* c = wearer->container(); c != nullptr && c->add(owner))
    {
        engine->get_map()->current_level().remove(owner);
        return true;
    }
    return false;
}

bool Pickable::use(pat::Actor* owner, pat::Actor* wearer, pat::Engine* engine)
{
    if (Container* c = wearer->container(); c != nullptr)
    {
        c->remove(owner);
        // delete owner from current level
        engine->get_map()->current_level().remove(owner);
        return true;
    }
    return false;
}

Pickable* Pickable::clone_impl() const
{
    return new Pickable(*this);
}