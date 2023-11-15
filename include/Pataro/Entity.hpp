#ifndef INCLUDE_PATARO_ENTITY_HPP
#define INCLUDE_PATARO_ENTITY_HPP

#include <Pataro/Action.hpp>
#include <Pataro/Animation.hpp>
#include <Pataro/Components/AI.hpp>
#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Components/Inventory.hpp>
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
        Entity(int x, int y, int ch, std::string  name, const tcod::ColorRGB& color);

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
        void morph_into(int ch, const tcod::ColorRGB& color);

        /**
         * @brief display the Entity on screen
         * 
         * @param console 
         * @param dt 
         * @param dx x offset on screen
         * @param dy y offset on screen
        */
        void render(tcod::Console& console, float dt, int dx = 0, int dy = 0) const;

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
        inline int  get_ch() const { return m_ch; }
        inline int  get_x() const { return m_x; }
        inline int  get_y() const { return m_y; }

        void put_at(int x, int y);
        void move(int dx, int dy);

        inline const std::string& get_name() const { return m_name; }
        inline void set_name(const std::string& name) { m_name = name; }

        inline bool is_blocking() const { return m_blocks; }
        inline void set_blocking(bool value) { m_blocks = value; }

        #pragma region "components getter & setters"
            inline component::Attacker* attacker() { return m_attacker.get(); }
            inline component::Destructible* destructible() { return m_destructible.get(); }
            inline component::AI* ai() { return m_ai.get(); }
            inline component::Inventory* inventory() { return m_inventory.get(); }
            inline component::Use* use() { return m_use.get(); }  // TODO: rename use to something else? like effect?

            inline std::unique_ptr<component::AI>&& move_ai() { return std::move(m_ai); }

            template <typename T, typename... Args> void set_attacker(Args&&... args) { m_attacker = std::make_unique<T>(std::forward<Args>(args)...); }
            template <typename T, typename... Args> void set_destructible(Args&&... args) { m_destructible = std::make_unique<T>(std::forward<Args>(args)...); }
            template <typename T, typename... Args> void set_ai(Args&&... args) { m_ai = std::make_unique<T>(std::forward<Args>(args)...); }
            template <typename T, typename... Args> void set_inventory(Args&&... args) { m_inventory = std::make_unique<T>(std::forward<Args>(args)...); }
            template <typename T, typename... Args> void set_use(Args&&... args) { m_use = std::make_unique<T>(std::forward<Args>(args)...); }

            inline void set_ai(std::unique_ptr<component::AI>&& arg) { m_ai = std::move(arg); }
        #pragma endregion

        friend class Animation;

    private:
        unsigned m_id;
        int m_x, m_y;       ///< Position of the Entity on the map
        int m_ch;           ///< ascii character representing the Entity
        std::string m_name;
        tcod::ColorRGB m_color;     ///< color of the ascii character

        float m_energy = 0.f;  ///< default energy level (needed for actions)
        // TODO make the speed variable when creating an entity (ie the user should be able to choose the speed)
        float m_speed = 1.f;   ///< default speed (needed to get energy, higher is better)
        bool m_blocks = true;  ///< Can we walk on this Entity?

        mutable std::unique_ptr<Animation> m_animation = nullptr;

        std::unique_ptr<component::Attacker>     m_attacker     = nullptr;  ///< For Entities that deal damages
        std::unique_ptr<component::Destructible> m_destructible = nullptr;  ///< For destructible Entities
        std::unique_ptr<component::AI>           m_ai           = nullptr;  ///< For self updating Entities
        std::unique_ptr<component::Inventory>    m_inventory    = nullptr;  ///< Something that can contain Entities
        std::unique_ptr<component::Use>          m_use          = nullptr;  ///< Something that can be used (create an action)
    };
}

#endif
