#ifndef PATARO_GUI_HPP
#define PATARO_GUI_HPP

#include <libtcod.hpp>

#include <memory>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include <sstream>

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
        void message(const TCODColor& color, Args&&... args)
        {
            std::ostringstream oss;
            ((oss << std::forward<Args>(args)), ...);

            // always ensure we still have place
            if (m_log.size() >= m_height - 1)
                m_log.erase(m_log.begin());

            // TODO check that the string isn't longer than the GUI display width
            m_log.emplace_back(oss.str(), color);
        }

        inline unsigned get_width()  { return m_width; }
        inline unsigned get_height() { return m_height; }

    private:
        void render_bar(int x, int y, int width, const std::string& name, float value, float max_val, const TCODColor& fg, const TCODColor& bg);

        struct Message {
            std::string text;
            TCODColor color;
            Message(const std::string& text, const TCODColor& color);
        };

        std::vector<Message> m_log;

        std::unique_ptr<TCODConsole> m_con;
        unsigned m_width, m_height;
        Proxy_t m_get_val;
    };
}

#endif
