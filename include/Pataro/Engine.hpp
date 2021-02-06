#ifndef PATARO_ENGINE_HPP
#define PATARO_ENGINE_HPP

#include <vector>
#include <string>
#include <memory>

#include <Pataro/Actor.hpp>
#include <Pataro/Map.hpp>

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
         */
        Engine(unsigned width, unsigned height, const std::string& title);

        /**
         * @brief move the player around
         * 
         */
        void update();

        /**
         * @brief Render all the actors
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

        inline void change_state(GameState state) { m_state = state; }
        inline Map* get_map() { return m_map.get(); }
        inline TCOD_key_t lastkey() { return m_lastkey; }

    private:
        GameState m_state = GameState::StartUp;

        std::shared_ptr<Actor> m_player;  ///< Pointer shared between the levels and the engine
        std::unique_ptr<Map> m_map;

        TCOD_key_t m_lastkey;
    };
}

#endif