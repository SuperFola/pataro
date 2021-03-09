#ifndef PATARO_ANIMATIONS_FACTORY_HPP
#define PATARO_ANIMATIONS_FACTORY_HPP

#include <Pataro/Animation.hpp>

#include <libtcod.hpp>

namespace pat::animation
{
    class Factory
    {
    public:
        /**
         * @brief Construct a new Factory object
         * 
         */
        Factory();

    private:
        TCODRandom* m_rng;
    };
}

#endif
