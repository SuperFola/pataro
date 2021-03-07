#include <Pataro/Components/Use/Heal.hpp>

#include <Pataro/Actions/Heal.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::component::details;

HealUse::HealUse(float quantity) :
    m_quantity(quantity)
{}

std::unique_ptr<pat::Action> HealUse::use(pat::Entity* source, [[maybe_unused]] pat::Engine* engine)
{
    return std::make_unique<pat::action::HealAction>(source, m_quantity);
}

HealUse* HealUse::clone_impl() const
{
    return new HealUse(*this);
}