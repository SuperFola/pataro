#include <Pataro/Map/Tile.hpp>

using namespace pat::map::details;

Tile::Tile(std::optional<bool> can_walk_)
{
    // if provided, alter the value
    if (can_walk_)
        can_walk = can_walk_.value();
}