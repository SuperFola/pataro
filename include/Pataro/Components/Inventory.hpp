#ifndef PATARO_COMPONENTS_INVENTORY_HPP
#define PATARO_COMPONENTS_INVENTORY_HPP

#include <vector>
#include <memory>

namespace pat
{
    class Entity;
}

namespace pat::component
{
    class Inventory
    {
    public:
        /**
         * @brief Construct a new Inventory object
         * 
         * @param size the number of elements in the inventory (0 = unlimited)
         */
        Inventory(std::size_t size);

        virtual ~Inventory() = default;

        /**
         * @brief Tries to add an entity (by copying it) to the inventory
         * 
         * @param entity 
         * @return true if we could add it (enough space)
         * @return false otherwise
         */
        bool add(Entity* entity);

        /**
         * @brief Remove an entity from the inventory (same id)
         * 
         * @param entity 
         */
        void remove(Entity* entity);

        /**
         * @brief Returns the entity at the given position
         * 
         * @param index 
         * @return const Entity& 
         */
        const Entity& operator[](std::size_t index) const;

        /**
         * @brief Returns a pointer to the object at the given index
         * 
         * @param index 
         * @return Entity* 
         */
        Entity* ptr_at(std::size_t index);

        /**
         * @brief Returns the current number of objects in the inventory
         * 
         * @return std::size_t 
         */
        std::size_t size() const;

        /**
         * @brief Returns the maximum capacity of the inventory
         * 
         * @return std::size_t 
         */
        std::size_t capacity() const;

        inline std::unique_ptr<Inventory> clone() const { return std::unique_ptr<Inventory>(clone_impl()); }

    protected:
        virtual Inventory* clone_impl() const;

    private:
        std::size_t m_max_size;
        std::vector<Entity> m_inventory;
    };
}

#endif
