#ifndef PATARO_GUI_HPP
#define PATARO_GUI_HPP

#include <libtcod.hpp>

#include <memory>
#include <string>
#include <functional>

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
         * @param destination a pointer to the console to draw on
         */
        Gui(unsigned width, unsigned height, const Proxy_t& proxy, TCODConsole* destination);

        void render();

    private:
        void render_bar(int x, int y, int width, const std::string& name, float value, float max_val, const TCODColor& fg, const TCODColor& bg);

        std::unique_ptr<TCODConsole> m_con;
        TCODConsole* m_dest;
        unsigned m_width, m_height;
        Proxy_t m_get_val;
    };
}

#endif
