#ifndef PATARO_MAP_CONSTANTS_HPP
#define PATARO_MAP_CONSTANTS_HPP

namespace pat::map::details
{
    constexpr int room_max_w = 12;
    constexpr int room_max_h = 12;

    constexpr int room_min_w = 6;
    constexpr int room_min_h = 6;

    constexpr int level_w = 80;
    constexpr int level_h = 50;

    constexpr int max_room_monsters = 3;
    constexpr int max_room_items    = 2;
}

#endif