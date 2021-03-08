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
    class Engine;

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
         * @param engine 
         * @param dest the destination TCOD console
         * @param x 
         * @param y 
         */
        void render(Engine* engine, TCODConsole* dest, int x, int y);

        template <typename... Args>
        void message(const TCODColor& color, Args&&... args)
        {
            std::ostringstream oss;
            ((oss << std::forward<Args>(args)), ...);

            // always ensure we still have place
            if (m_log.size() >= m_height - 1)
                m_log.erase(m_log.begin());

            std::string out = oss.str();
            do
            {
                std::size_t pos = out.find('\n');
                m_log.emplace_back(out.substr(0, pos), color);

                if (pos != std::string::npos)
                    out = out.substr(pos);
            } while (out.find('\n') != std::string::npos);
            // TODO check that the string isn't longer than the GUI display width
        }

        inline unsigned get_width()  { return m_width; }
        inline unsigned get_height() { return m_height; }

    private:
        /**
         * @brief Render a bar on the panel, given a text, color, position and val/max_val
         * 
         * @param x on panel position
         * @param y on panel position
         * @param width max bar length
         * @param name 
         * @param value 
         * @param max_val 
         * @param fg color for the bar
         * @param bg background color for the bar
         */
        void render_bar(int x, int y, int width, const std::string& name, float value, float max_val, const TCODColor& fg, const TCODColor& bg);

        void render_mouse_look(Engine* engine);

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
