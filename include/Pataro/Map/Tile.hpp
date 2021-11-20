#ifndef PATARO_MAP_TILE_HPP
#define PATARO_MAP_TILE_HPP

namespace pat::map::details
{
    struct Tile
    {
        bool explored = false;  ///< Has the player seen this tile?

        Tile();

        template<class Archive>
        void save(Archive& archive) const {
            archive(cereal::make_nvp("isExplored", explored));
        }

        template<class Archive>
        void load(Archive& archive) {
            archive(explored);
        }
    };
}

#endif