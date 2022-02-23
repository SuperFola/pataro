#ifndef PATARO_COMPONENTS_CONTAINER_HPP
#define PATARO_COMPONENTS_CONTAINER_HPP

#include <cereal/types/memory.hpp>
#include <cereal/access.hpp>

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

        /**
         * @brief Tries to add an entity (by copying it) to the container
         * 
         * @param entity 
         * @return true if we could add it (enough space)
         * @return false otherwise
         */
        bool add(Entity* entity);

        /**
         * @brief Remove an entity from the container (same id)
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
         * @brief Returns the current number of objects in the container
         * 
         * @return std::size_t 
         */
        std::size_t size() const;

        /**
         * @brief Returns the maximum capacity of the container
         * 
         * @return std::size_t 
         */
        std::size_t capacity() const;

        inline std::unique_ptr<Container> clone() const { return std::unique_ptr<Container>(clone_impl()); }

        template <typename Archive>
        void save(Archive& archive) const
        {
            archive(cereal::make_nvp("MaxSize", m_max_size), cereal::make_nvp("Inventory", m_inventory));
        }

        template <typename Archive>
        void load(Archive& archive)
        {
            archive(m_max_size, m_inventory);
        }

        template <typename Archive>
        static void load_and_construct(Archive& archive, cereal::construct<Container>& construct)
        {
            archive(construct->m_max_size, construct->m_inventory);
        }

    protected:
        virtual Container* clone_impl() const;

    private:
        std::size_t m_max_size;
        std::vector<Entity> m_inventory;
    };
}

#endif
