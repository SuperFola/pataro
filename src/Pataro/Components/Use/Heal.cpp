#include <Pataro/Components/Use/Heal.hpp>

#include <Pataro/Actions/Heal.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::component::details;

HealUse::HealUse(pat::Entity* source, float quantity) :
    Use(source), m_quantity(quantity)
{}

std::unique_ptr<pat::Action> HealUse::operator()([[maybe_unused]] pat::Engine* engine)
{
    return std::make_unique<pat::action::HealAction>(m_source, m_quantity);
}

HealUse* HealUse::clone_impl() const
{
    return new HealUse(*this);
}