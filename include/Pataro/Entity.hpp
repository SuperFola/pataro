#ifndef PATARO_ENTITY_HPP
#define PATARO_ENTITY_HPP

#include <Pataro/Action.hpp>
#include <Pataro/Animation.hpp>
#include <Pataro/Components/AI.hpp>
#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Components/Container.hpp>
#include <Pataro/Components/Use.hpp>

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
        static unsigned Id;

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
         * @brief Construct a new Entity object
         * 
         * @param other 
         */
        Entity(const Entity& other);

        /**
         * @brief Copy an entity
         * 
         * @param other 
         * @return Entity& 
         */
        Entity& operator=(const Entity& other);

        /**
         * @brief Morph the Entity into... something else
         * 
         * @param ch 
         * @param color 
         */
        void morph_into(int ch, const TCODColor& color);

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

        /**
         * @brief Increase the energy count with the entity speed
         * 
         */
        void gain_energy();

        /**
         * @brief Checks if the entity has enough energy to perform an action
         * 
         * @return true 
         * @return false 
         */
        bool has_enough_energy() const;

        /**
         * @brief Set the animation object
         * 
         * @param anim 
         */
        void set_animation(const Animation& anim);

        inline unsigned id() const { return m_id; }
        inline int  get_x() const { return m_x; }
        inline int  get_y() const { return m_y; }

        void put_at(int x, int y);
        void move(int dx, int dy);

        inline const std::string& get_name() const { return m_name; }
        inline void set_name(const std::string& name) { m_name = name; }

        inline bool is_blocking() const { return m_blocks; }
        inline void set_blocking(bool value) { m_blocks = value; }

        #define GET_CMPNT(Type, name)  inline component::Type* name() { return m_##name.get(); }
        #define SET_CMPNT1(name)       template <typename T, typename... Args> void set_##name(Args&&... args) { m_##name = std::make_unique<T>(std::forward<Args>(args)...); }
        #define SET_CMPNT2(Type, name) inline void set_##name(std::unique_ptr<component::Type>&& arg) { m_##name = std::move(arg); }
        #define GET_SET_CMPNT(Type, name) GET_CMPNT(Type, name) SET_CMPNT1(name) SET_CMPNT2(Type, name)

            GET_SET_CMPNT(Attacker, attacker)
            GET_SET_CMPNT(Destructible, destructible)
            GET_SET_CMPNT(AI, ai)
            GET_SET_CMPNT(Container, container)
            GET_SET_CMPNT(Use, use)

        #undef GET_SET_CMPNT
        #undef SET_COMPONENT
        #undef GET_COMPONENT

        friend class Animation;

    private:
        unsigned m_id;
        int m_x, m_y;       ///< Position of the Entity on the map
        int m_ch;           ///< ascii character representing the Entity
        std::string m_name;
        TCODColor m_color;     ///< color of the ascii character

        float m_energy = 0.f;  ///< default energy level (needed for actions)
        // TODO make the speed variable when creating an entity (ie the user should be able to choose the speed)
        float m_speed = 1.f;   ///< default speed (needed to get energy, higher is better)
        bool m_blocks = true;  ///< Can we walk on this Entity?

        mutable std::unique_ptr<Animation> m_animation = nullptr;

        std::unique_ptr<component::Attacker>     m_attacker     = nullptr;  ///< For Entities that deal damages
        std::unique_ptr<component::Destructible> m_destructible = nullptr;  ///< For destructible Entities
        std::unique_ptr<component::AI>           m_ai           = nullptr;  ///< For self updating Entities
        std::unique_ptr<component::Container>    m_container    = nullptr;  ///< Something that can contain Entities
        std::unique_ptr<component::Use>          m_use          = nullptr;  ///< Something that can be used (create an action)
    };
}

#endif
