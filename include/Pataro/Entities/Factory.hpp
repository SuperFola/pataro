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

        /**
         * @brief Generate a random monster
         * 
         * @param x position on the map
         * @param y position on the map
         * @param difficulty scaling difficulty factor. Less than 1 means easy, greater than 1 means harder
         * @return std::shared_ptr<Entity> 
         */
        std::shared_ptr<Entity> get_random_monster(int x, int y, float difficulty=1.f);

        /**
         * @brief Generate a random monster
         * 
         * @param x position on the map
         * @param y position on the map
         * @return std::shared_ptr<Entity> 
         */
        std::shared_ptr<Entity> get_random_item(int x, int y);

    private:
        TCODRandom* m_rng;
    };
}

#endif
