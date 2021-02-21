#ifndef PATARO_ACTOR_HPP
#define PATARO_ACTOR_HPP

#include <Pataro/Actor/AI.hpp>
#include <Pataro/Actor/Attacker.hpp>
#include <Pataro/Actor/Destructible.hpp>
#include <Pataro/Actor/Pickable.hpp>
#include <Pataro/Actor/Container.hpp>

#include <libtcod.hpp>

#include <string>
#include <utility>
#include <memory>

namespace pat
{
    class Engine;

    /**
     * @brief An actor class representing items, traps, doors, monsters, players...
     * @details It uses composition to represent all of those kind of actors.
     * 
     */
    class Actor
    {
    public:
        /**
         * @brief Construct a new Actor object
         * 
         * @param x position on X axis
         * @param y position on Y axis
         * @param ch ascii code representing the character
         * @param name the name of the actor
         * @param color the color for the actor
        */
        Actor(int x, int y, int ch, const std::string& name, const TCODColor& color);

        /**
         * @brief Construct a new Actor object
         * 
         * @param actor 
         */
        Actor(const Actor& actor);

        /**
         * @brief Morph the actor into... something else
         * 
         * @param ch 
         * @param name 
         * @param color 
         */
        void morph_into(int ch, const std::string& name, const TCODColor& color);

        /**
         * @brief display the actor on screen
         * 
         * @param dx x offset on screen
         * @param dy y offset on screen
        */
        void render(int dx=0, int dy=0) const;

        /**
         * @brief Update the actor
         * 
         * @param engine 
         */
        void update(Engine* engine);

        inline int  get_x() const { return m_x; }
        inline int  get_y() const { return m_y; }
        inline void put_at(int x, int y) { m_x = x; m_y = y; }

        inline const std::string& get_name() const { return m_name; }

        inline bool is_blocking() const { return m_blocks; }
        inline void set_blocking(bool value) { m_blocks = value; }

        inline unsigned long long id() const { return m_id; }

        #define GET_COMPONENT(Type, name)                        \
            inline actor::Type* name() { return m_##name.get(); }

        GET_COMPONENT(Attacker, attacker)
        GET_COMPONENT(Destructible, destructible)
        GET_COMPONENT(AI, ai)
        GET_COMPONENT(Pickable, pickable)
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
        SET_COMPONENT(pickable)
        SET_COMPONENT(container)

        #undef SET_COMPONENT

    private:
        int m_x, m_y;  ///< Position of the actor on the map
        int m_ch;  ///< ascii character representing the actor
        std::string m_name;
        TCODColor m_color;
        unsigned long long m_id;

        bool m_blocks = true;  ///< Can we walk on this actor?
        std::unique_ptr<actor::Attacker> m_attacker = nullptr;  ///< For actors that deal damages
        std::unique_ptr<actor::Destructible> m_destructible = nullptr;  ///< For destructible actors
        std::unique_ptr<actor::AI> m_ai = nullptr;  ///< For self updating actors
        std::unique_ptr<actor::Pickable> m_pickable = nullptr;  ///< Something that can be picked up and used
        std::unique_ptr<actor::Container> m_container = nullptr;  ///< Something that can contain actors
    };
}

#endif
