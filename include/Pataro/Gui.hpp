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
        /**
         * @brief Construct a new Gui object
         * 
         * @param width size of the GUI console
         * @param height size of the GUI console
         * @param proxy a function to retrieve the value and the max value
         */
        Gui(unsigned width, unsigned height, const std::function<void(float*, float*)>& proxy);

        void render();

    private:
        void render_bar(int x, int y, int width, const std::string& name, float value, float max_val, const TCODColor& fg, const TCODColor& bg);

        std::unique_ptr<TCODConsole> m_con;
        std::function<void(float*, float*)> m_get_val;
    };
}

#endif
