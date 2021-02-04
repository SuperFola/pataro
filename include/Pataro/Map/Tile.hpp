#ifndef PATARO_MAP_TILE_HPP
#define PATARO_MAP_TILE_HPP

namespace pat::map
{
    struct Tile
    {
        bool can_walk = true;  ///< Can we walk through the tile?

        Tile();
    };
}

#endif