#ifndef PATARO_MAP_TILE_HPP
#define PATARO_MAP_TILE_HPP

#include <optional>

namespace pat::map::details
{
    struct Tile
    {
        bool can_walk = true;  ///< Can we walk through the tile?

        Tile(std::optional<bool> can_walk = {});
    };
}

#endif