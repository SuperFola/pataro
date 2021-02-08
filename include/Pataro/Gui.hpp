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
        using Pos_t = std::pair<int, int>;

        /**
         * @brief Construct a new Gui object
         * 
         * @param width size of the GUI console
         * @param height size of the GUI console
         * @param proxy a function to retrieve the value and the max value
         * @param dest a pointer to the console to draw on
         * @param pos position where to draw
         */
        Gui(unsigned width, unsigned height, const Proxy_t& proxy, TCODConsole* dest, const Pos_t& pos);

        void render();

    private:
        void render_bar(const Pos_t& pos, int width, const std::string& name, float value, float max_val, const TCODColor& fg, const TCODColor& bg);

        std::unique_ptr<TCODConsole> m_con;
        unsigned m_width, m_height;
        Proxy_t m_get_val;
        TCODConsole* m_dest;
        Pos_t m_pos;
    };
}

#endif
