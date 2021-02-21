#ifndef PATARO_ACTOR_CONTAINER_HPP
#define PATARO_ACTOR_CONTAINER_HPP

#include <vector>
#include <memory>

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

        /**
         * @brief Clone the class
         * 
         * @return std::unique_ptr<Container> 
         */
        inline std::unique_ptr<Container> clone() const { return std::unique_ptr<Container>(clone_impl()); }

    protected:
        virtual Container* clone_impl() const;

    private:
        std::size_t m_max_size;
        std::vector<Actor> m_inventory;
    };
}

#endif
