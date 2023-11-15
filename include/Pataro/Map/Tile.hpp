#ifndef PATARO_MAP_TILE_HPP
#define PATARO_MAP_TILE_HPP

namespace pat::map
{
    struct Tile
    {
        bool explored = false;  ///< Has the player seen this tile?
        enum class Type
        {
            Wall,
            Ground,
            Stairs
        } type;

        explicit Tile(Type type = Type::Wall);
    };
}

#endif