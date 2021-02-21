#include <Pataro/Actor/Pickable/Healer.hpp>

#include <Pataro/Actor.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Actor/Destructible.hpp>

using namespace pat::actor::details;

Healer::Healer(float amount) :
    m_amount(amount)
{}

bool Healer::use(pat::Actor* owner, pat::Actor* wearer, pat::Engine* engine)
{
    if (Destructible* d = wearer->destructible(); d != nullptr)
    {
        float healed = d->heal(m_amount);
        if (healed > 0.f)  // if it healed anything, mark it as used
            // FIXME very ugly, make it better
            return Pickable::use(owner, wearer, engine);
    }
    return true;
}

Healer* Healer::clone_impl() const
{
    return new Healer(*this);
}