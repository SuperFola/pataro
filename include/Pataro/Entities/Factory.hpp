#ifndef PATARO_ENTITIES_FACTORY_HPP
#define PATARO_ENTITIES_FACTORY_HPP

#include <Pataro/Entity.hpp>

#include <libtcod.hpp>

#include <memory>

namespace pat::entity
{
    class Factory
    {
    public:
        /**
         * @brief Construct a new Factory object
         * 
         */
        Factory();

        std::shared_ptr<Entity> get_random_monster(int x, int y);

    private:
        TCODRandom* m_rng;
    };
}

#endif
