#ifndef PATARO_UTILS_HPP
#define PATARO_UTILS_HPP

#include <string>

namespace pat::details
{
    /**
     * @brief Returns the current date as a string
     * 
     * @return std::string 
     */
    std::string date_to_string();

    /**
     * @brief Get the manhattan distance
     * 
     * @param x1 
     * @param y1 
     * @param x2 
     * @param y2 
     * @return unsigned 
     */
    unsigned get_manhattan_distance(int x1, int y1, int x2, int y2);
}

#endif
