#ifndef INCLUDE_PATARO_CONFIG_HPP
#define INCLUDE_PATARO_CONFIG_HPP

#include <vector>
#include <libtcod.hpp>

namespace pat
{
    struct Config
    {
        struct Tile
        {
            char repr;
            tcod::ColorRGB color_visible;
            tcod::ColorRGB color_outside_fov;
        };

        /**
         * @brief Construct a new Tile object ; shorthand for tiles with the same color when visible/outside of fov (but explored)
         * 
         * @param repr 
         * @param color 
         */
        static Tile tile(char repr, tcod::ColorRGB color)
        {
            return Tile { repr, color, color };
        }

        struct Theme
        {
            Tile wall;
            Tile ground;
        };

        std::vector<Theme> themes;
    };
}

#endif
