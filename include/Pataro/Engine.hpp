#ifndef PATARO_ENGINE_HPP
#define PATARO_ENGINE_HPP

#include <vector>
#include <string>
#include <memory>

#include <Pataro/Entity.hpp>
#include <Pataro/Map.hpp>
#include <Pataro/Gui.hpp>

namespace pat
{
    enum class GameState
    {
        StartUp,
        Idle,
        NewTurn,
        Victory,
        Defeat
    };

    class Engine
    {
    public:
        /**
         * @brief Construct a new Engine object
         * 
         * @param width width of the window
         * @param height height of the window
         * @param title title of the window
         * @param show_debug default: false. Show debug gui
         */
        Engine(unsigned width, unsigned height, const std::string& title, bool show_debug = false);

        /**
         * @brief move the player around
         * 
         */
        void update();

        /**
         * @brief Render all the Entities
         * @details It flushes the screen at the end.
         * 
         */
        void render();

        /**
         * @brief Check if the engine is still running, i.e. if the window is opened
         * 
         * @return true 
         * @return false 
         */
        bool is_running() const;

        /**
         * @brief Pick a tile in a given range
         * 
         * @param x output, pointer to integer
         * @param y output, pointer to integer
         * @param max_range default to 0.f
         * @return true 
         * @return false the action was canceled
         */
        bool pick_a_tile(int* x, int* y, float max_range = 0.f);

        inline unsigned width()  { return m_width; }
        inline unsigned height() { return m_height; }

        inline void change_state(GameState state) { m_state = state; }
        inline Entity* get_player() { return m_player.get(); }
        inline Map*    get_map()    { return m_map.get(); }
        inline Gui*    get_gui()    { return m_gui.get(); }
        inline const TCOD_key_t&   lastkey() { return m_lastkey; }
        inline const TCOD_mouse_t& mouse()   { return m_mouse; }

    private:
        unsigned m_width, m_height;
        bool m_show_debug;
        TCOD_key_t m_lastkey;
        TCOD_mouse_t m_mouse;

        GameState m_state = GameState::StartUp;

        std::shared_ptr<Entity> m_player;  ///< Pointer shared between the levels and the engine
        std::unique_ptr<Map> m_map;
        std::unique_ptr<Gui> m_gui;
    };
}

#endif