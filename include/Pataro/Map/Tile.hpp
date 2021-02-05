#ifndef PATARO_MAP_TILE_HPP
#define PATARO_MAP_TILE_HPP

namespace pat::map::details
{
    struct Tile
    {
        bool explored = false;  ///< Has the player seen this tile?

        Tile();
    };
}

#endif