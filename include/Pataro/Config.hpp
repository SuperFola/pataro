#ifndef INCLUDE_PATARO_CONFIG_HPP
#define INCLUDE_PATARO_CONFIG_HPP

#include <array>
#include <vector>
#include <libtcod.hpp>

namespace pat
{
    struct Config
    {
        struct Tile
        {
            unsigned char repr {'#'};
            tcod::ColorRGB color_visible;
            tcod::ColorRGB color_outside_fov;
        };

        /**
         * @brief Construct a new Tile object ; shorthand for tiles with the same color when visible/outside of fov (but explored)
         * 
         * @param repr 
         * @param color 
         */
        static Tile tile(unsigned char repr, tcod::ColorRGB color)
        {
            return Tile { repr, color, color };
        }


        struct Theme
        {
            // Ground = 0, Wall = 1, Stairs = 2
            std::array<Tile, 3> colors;
        };

        std::vector<Theme> themes;
        int fps_max = 30;
    };
}

#endif
