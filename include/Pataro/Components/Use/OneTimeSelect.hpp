#ifndef COMPONENTS_USE_ONETIMESELECT_HPP
#define COMPONENTS_USE_ONETIMESELECT_HPP

#include <Pataro/Action.hpp>
#include <Pataro/Components/Use.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>

#include <string>
#include <functional>
#include <memory>

namespace pat::component
{
    /**
     * @brief Describe an action to perform using a PickTile instance
     * 
     */
    enum class PickMethod
    {
        Simple,       ///< Pick a single tile without any check
        LivingEntity  ///< Pick a single tile with a living entity
    };

    class PickTile
    {
    public:
        /**
         * @brief Construct a new Pick Tile object
         * 
         * @param method describe an action to perform using this class
         * @param range range available for the selection
         */
        PickTile(PickMethod method, float range);

        /**
         * @brief Run the selected method
         * 
         * @param engine 
         * @return true 
         * @return false 
         */
        bool pick(Engine* engine);

        inline PickMethod get_method() const { return m_method; }
        inline int get_x() const { return m_x; }
        inline int get_y() const { return m_y; }
        inline float get_range() const { return m_range; }
        inline Entity* get_entity() const { return m_entity; }

    protected:
        /**
         * @brief Pick a single tile, without any following check
         * 
         * @param engine 
         * @return true if a tile was picked
         * @return false 
         */
        bool simple(Engine* engine);

        /**
         * @brief Pick a single tile and check that a living entity is on it
         * 
         * @param engine 
         * @return true if a living entity was picked
         * @return false 
         */
        bool live_entity(Engine* engine);

    private:
        PickMethod m_method;
        int m_x, m_y;
        float m_range;
        Entity* m_entity;
    };

    template <typename A, typename... Args>
    class OneTimeSelectUse : public Use
    {
    public:
        using Callback_t = std::function<std::unique_ptr<Action>(Entity* source, Entity* owner, const PickTile& picker)>;

        /**
         * @brief Construct a new One Time Select Use object, to launch an action taking a single argument
         * 
         * @param left_click_text the text related to the left-click action
         * @param range the range in which the click can be performed
         * @param args 
         */
        OneTimeSelectUse(const std::string& left_click_text, PickTile picker, Args&&... args) :
            m_text(left_click_text), m_picker(picker)
        {
            m_function = [args = std::make_tuple(std::forward<Args>(args) ...)](Entity* source, Entity* owner, const PickTile& picker) -> std::unique_ptr<Action> {
                return std::apply([source, owner, &picker](auto&&... args) {
                    return std::make_unique<A>(source, owner, &picker, args...);
                }, std::move(args));
            };
        }

    protected:
        std::unique_ptr<Action> use(Entity* source, Entity* owner, [[maybe_unused]] Engine* engine) override
        {
            engine->get_gui()->message(colors::cyan, "Left-click ", m_text, ",\nor right-click to cancel.");
            if (!m_picker.pick(engine))
                return nullptr;
            return m_function(source, owner, m_picker);
        }

        OneTimeSelectUse<A, Args...>* clone_impl() const override
        {
            return new OneTimeSelectUse<A, Args...>(m_text, m_picker, m_function);
        }

    private:
        OneTimeSelectUse(const std::string& text, const PickTile& picker, const Callback_t& callback) :
            m_text(text), m_picker(picker), m_function(callback)
        {}

        std::string m_text;
        PickTile m_picker;
        Callback_t m_function;
    };
}

#endif
