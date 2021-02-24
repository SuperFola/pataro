#include <Pataro/Action.hpp>

#include <Pataro/Engine.hpp>

using namespace pat;

ActionResult Action::perform([[maybe_unused]] pat::Engine* engine)
{
    return ActionResult::Success;
}