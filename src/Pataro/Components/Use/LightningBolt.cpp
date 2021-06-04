#include <Pataro/Components/Use/LightningBolt.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Actions/LightningBolt.hpp>

using namespace pat::component::details;

LightningBoltUse::LightningBoltUse(float range, float damage) :
    m_range(range), m_damage(damage)
{}

std::unique_ptr<pat::Action> LightningBoltUse::use(pat::Entity* source, pat::Entity* owner, [[maybe_unused]] pat::Engine* engine)
{
    return std::make_unique<pat::LightningBoltAction>(source, owner, m_range, m_damage);
}

LightningBoltUse* LightningBoltUse::clone_impl() const
{
    return new LightningBoltUse(*this);
}