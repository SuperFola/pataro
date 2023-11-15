#ifndef INCLUDE_PATARO_ENGINE_HPP
#define INCLUDE_PATARO_ENGINE_HPP

#include <vector>
#include <string>
#include <memory>
#include <map>

#include <Pataro/Entity.hpp>
#include <Pataro/Map.hpp>
#include <Pataro/Gui.hpp>
#include <Pataro/Config.hpp>

#include <libtcod.hpp>
#include <libtcod/timer.hpp>
#include <SDL2/SDL_keycode.h>

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

    struct Mouse
    {
        int cx, cy;  ///< Cell position
        bool lbutton_pressed;
        bool rbutton_pressed;
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
         * @param config engine configuration
         * @param show_debug default: false. Show debug gui
         */
        Engine(unsigned width, unsigned height, const std::string& title, Config  config, bool show_debug = false);

        /**
         * @brief Initialize the engine
         * 
         */
        void reset();

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

        void handle_events();

        /**
         * @brief Check if the engine is still running, i.e. if the window is opened
         * 
         * @return true 
         * @return false 
         */
        [[nodiscard]] inline bool is_running() const { return m_running; }

        /**
         * @brief Log an event with a given name. Only names/occurences are kept
         * 
         * @param name 
         */
        void log(const std::string& name);

        /**
         * @brief Export game log to file
         * 
         */
        void export_log();

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

        /**
         * @brief Prompts the player to select an object in its inventory
         * 
         * @param owner 
         * @return Entity* nullptr if nothing selected
         */
        Entity* choose_from_inventory(Entity* owner);

        void render_defeat();

        [[nodiscard]] inline unsigned width() const  { return m_width; }
        [[nodiscard]] inline unsigned height() const { return m_height; }

        inline void change_state(GameState state) { m_state = state; }
        inline Entity* get_player() { return m_player.get(); }
        inline Map*    get_map()    { return m_map.get(); }
        inline Gui*    get_gui()    { return m_gui.get(); }
        [[nodiscard]] inline const SDL_Keycode& lastkey() const { return m_lastkey; }
        inline const Mouse& mouse() { return m_mouse; }

        inline tcod::Console& console() { return m_console; }
        inline void flush()             { m_context.present(m_console); }

    private:
        unsigned m_width, m_height;  // TODO: move to config
        Config m_config;
        bool m_show_debug;
        bool m_running;
        SDL_Keycode m_lastkey;
        Mouse m_mouse;

        tcod::Console m_console;
        tcod::Context m_context;
        tcod::Timer m_timer;

        GameState m_state = GameState::StartUp;

        std::shared_ptr<Entity> m_player;  ///< Pointer shared between the levels and the engine
        std::unique_ptr<Map> m_map;
        std::unique_ptr<Gui> m_gui;

        std::map<std::string, unsigned> m_log;
        int m_scroll_pos = 0;
    };
}

#endif
