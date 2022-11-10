#ifndef PATARO_CONSTANTS_HPP
#define PATARO_CONSTANTS_HPP

#define PATARO_GATHER_ANON_STATS

#include <array>

namespace pat::details
{
    constexpr int player_fov = 10;
    constexpr std::array<int, 9> frame = {
        201, 205, 187,
        186,  32, 186,
        200, 205, 188
    };
}

#endif
