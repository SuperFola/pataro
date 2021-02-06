#ifndef PATARO_ENGINE_HPP
#define PATARO_ENGINE_HPP

#include <vector>
#include <string>
#include <memory>

#include <Pataro/Actor.hpp>
#include <Pataro/Map.hpp>

namespace pat
{
    enum class GameStatus
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

    private:
        GameStatus m_state = GameStatus::StartUp;
        Actor* m_player;  ///< Managed ptr by a level in the map
        int m_fov_radius = 10;
        bool m_compute_fov = true;
        std::unique_ptr<Map> m_map;
    };
}

#endif