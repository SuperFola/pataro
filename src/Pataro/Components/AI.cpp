#include <Pataro/Components/AI.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

using namespace pat::component;

AI* AI::clone_impl() const
{
    return new AI(*this);
}