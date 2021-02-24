#ifndef PATARO_ENTITY_HPP
#define PATARO_ENTITY_HPP

#include <Pataro/Action.hpp>
#include <Pataro/Components/AI.hpp>
#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Components/Container.hpp>

#include <libtcod.hpp>

#include <string>
#include <utility>
#include <memory>

namespace pat
{
    class Engine;

    /**
     * @brief An entity class representing items, traps, doors, monsters, players...
     * @details It uses composition to represent all of those kind of entity.
     * 
     */
    class Entity
    {
    public:
        /**
         * @brief Construct a new Entity object
         * 
         * @param x position on X axis
         * @param y position on Y axis
         * @param ch ascii code representing the character
         * @param name the name of the entity
         * @param color the color for the entity
        */
        Entity(int x, int y, int ch, const std::string& name, const TCODColor& color);

        /**
         * @brief Morph the Entity into... something else
         * 
         * @param ch 
         * @param name 
         * @param color 
         */
        void morph_into(int ch, const std::string& name, const TCODColor& color);

        /**
         * @brief display the Entity on screen
         * 
         * @param dx x offset on screen
         * @param dy y offset on screen
        */
        void render(int dx=0, int dy=0) const;

        /**
         * @brief Update the Entity
         * 
         * @param engine 
         * @return std::unique_ptr<Action> the action to perform
         */
        std::unique_ptr<Action> update(Engine* engine);

        inline int  get_x() const { return m_x; }
        inline int  get_y() const { return m_y; }

        void put_at(int x, int y);
        void move(int dx, int dy);

        inline const std::string& get_name() const { return m_name; }

        inline bool is_blocking() const { return m_blocks; }
        inline void set_blocking(bool value) { m_blocks = value; }

        #define GET_COMPONENT(Type, name)                        \
            inline component::Type* name() { return m_##name.get(); }

        GET_COMPONENT(Attacker, attacker)
        GET_COMPONENT(Destructible, destructible)
        GET_COMPONENT(AI, ai)
        GET_COMPONENT(Container, container)

        #undef GET_COMPONENT

        #define SET_COMPONENT(name)                 \
            template <typename T, typename... Args> \
            void set_##name(Args&&... args)         \
            {                                       \
                m_##name = std::make_unique<T>(     \
                    std::forward<Args>(args)...     \
                );                                  \
            }

        SET_COMPONENT(attacker)
        SET_COMPONENT(destructible)
        SET_COMPONENT(ai)
        SET_COMPONENT(container)

        #undef SET_COMPONENT

    private:
        int m_x, m_y;       ///< Position of the Entity on the map
        int m_ch;           ///< ascii character representing the Entity
        std::string m_name;
        TCODColor m_color;  ///< color of the ascii character

        bool m_blocks = true;  ///< Can we walk on this Entity?
        std::unique_ptr<component::Attacker>     m_attacker     = nullptr;  ///< For Entities that deal damages
        std::unique_ptr<component::Destructible> m_destructible = nullptr;  ///< For destructible Entities
        std::unique_ptr<component::AI>           m_ai           = nullptr;  ///< For self updating Entities
        std::unique_ptr<component::Container>    m_container    = nullptr;  ///< Something that can contain Entities
    };
}

#endif
