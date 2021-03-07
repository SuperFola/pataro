#ifndef PATARO_COMPONENTS_CONTAINER_HPP
#define PATARO_COMPONENTS_CONTAINER_HPP

#include <vector>
#include <memory>

namespace pat
{
    class Entity;
}

namespace pat::component
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

        bool add(Entity* actor);

        void remove(Entity* actor);

        inline std::unique_ptr<Container> clone() const { return std::unique_ptr<Container>(clone_impl()); }

    protected:
        virtual Container* clone_impl() const;

    private:
        std::size_t m_max_size;
        std::vector<Entity> m_inventory;
    };
}

#endif
