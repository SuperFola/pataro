#ifndef PATARO_GUI_HPP
#define PATARO_GUI_HPP

#include <libtcod.hpp>

#include <memory>
#include <string>
#include <functional>
#include <utility>

namespace pat
{
    class Gui
    {
    public:
        using Proxy_t = std::function<void(float*, float*)>;

        /**
         * @brief Construct a new Gui object
         * 
         * @param width size of the GUI console
         * @param height size of the GUI console
         * @param proxy a function to retrieve the value and the max value
         */
        Gui(unsigned width, unsigned height, const Proxy_t& proxy);

        /**
         * @brief Render the GUI on a given TCOD console
         * 
         * @param dest 
         * @param x 
         * @param y 
         */
        void render(TCODConsole* dest, int x, int y);

        template <typename... Args>
        void message(const TCODColor& color, const char* text, Args&&... args)
        {}

        inline unsigned get_width()  { return m_width; }
        inline unsigned get_height() { return m_height; }

    private:
        void render_bar(int x, int y, int width, const std::string& name, float value, float max_val, const TCODColor& fg, const TCODColor& bg);

        std::unique_ptr<TCODConsole> m_con;
        unsigned m_width, m_height;
        Proxy_t m_get_val;
    };
}

#endif
