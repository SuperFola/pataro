#ifndef PATARO_ACTOR_CONTAINER_HPP
#define PATARO_ACTOR_CONTAINER_HPP

#include <vector>

namespace pat
{
    class Actor;
}

namespace pat::actor
{
    class Container
    {
    public:
        /**
         * @brief Construct a new Container object
         * 
         * @param size the number of elements in the container (0 = unlimited)
         */
        Container(std::size_t size);

        bool add(Actor* actor);

        void remove(Actor* actor);

    private:
        std::size_t m_max_size;
        std::vector<Actor*> m_inventory;
    };
}

#endif
