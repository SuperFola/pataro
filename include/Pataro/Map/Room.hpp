#ifndef PATARO_MAP_ROOM_HPP
#define PATARO_MAP_ROOM_HPP

#include <cereal/types/memory.hpp>
#include <cereal/access.hpp>

namespace pat::map::details
{
    struct Room
    {
    public:
        /**
         * @brief Construct a new Room object
         * 
         * @param x 
         * @param y 
         * @param w 
         * @param h 
         */
        Room(int x, int y, int w, int h);

        const int x, y, width, height;

        template <typename Archive>
        void save(Archive& archive) const
        {
            archive(
                cereal::make_nvp("X", x),
                cereal::make_nvp("Y", y),
                cereal::make_nvp("width", width),
                cereal::make_nvp("height", height));
        }

        template <typename Archive>
        void load(Archive& archive)
        {
            archive(x, y, width, height);
        }
    };
}

#endif
