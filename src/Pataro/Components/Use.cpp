#include <Pataro/Components/Use.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::component;

Use::Use(pat::Entity* source) :
    m_source(source)
{}

std::unique_ptr<pat::Action> Use::operator()([[maybe_unused]] pat::Engine* engine)
{
    return nullptr;
}

Use* Use::clone_impl() const
{
    return new Use(*this);
}