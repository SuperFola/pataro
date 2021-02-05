#ifndef PATARO_ENGINE_HPP
#define PATARO_ENGINE_HPP

#include <vector>
#include <string>
#include <memory>

#include <Pataro/Actor.hpp>
#include <Pataro/Map/Map.hpp>

namespace pat
{
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
        std::vector<std::unique_ptr<Actor>> m_actors;
        Actor* m_player;  ///< Pointer managed by a unique_ptr in m_actors
        std::unique_ptr<Map> m_map;
    };
}

#endif