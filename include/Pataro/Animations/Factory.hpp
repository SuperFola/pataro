#ifndef PATARO_ANIMATIONS_FACTORY_HPP
#define PATARO_ANIMATIONS_FACTORY_HPP

#include <Pataro/Animation.hpp>

#include <libtcod.hpp>

namespace pat
{
    class Entity;
}

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

        /**
         * @brief Create a lightning bolt animation
         * 
         * @param target 
         * @return Animation 
         */
        static Animation lightningBolt(Entity* target);

        /**
         * @brief Create a burning animation
         * 
         * @param target 
         * @return Animation 
         */
        static Animation burning(Entity* target);

    private:
        TCODRandom* m_rng;
    };
}

#endif
