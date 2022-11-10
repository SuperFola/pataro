#ifndef INCLUDE_PATARO_GUI_HPP
#define INCLUDE_PATARO_GUI_HPP

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
        void render(Engine* engine, TCOD_Console* dest, int x, int y);

        template <typename... Args>
        void message(const tcod::ColorRGB& color, Args&&... args)
        {
            std::ostringstream oss;
            ((oss << std::forward<Args>(args)), ...);
            std::string out = oss.str();

            if (out.find('\n') == std::string::npos)
                m_log.emplace_back(out, color);
            else
            {
                while (true)
                {
                    std::size_t pos = out.find('\n');
                    if (pos == std::string::npos)
                    {
                        m_log.emplace_back(out, color);
                        break;
                    }

                    m_log.emplace_back(out.substr(0, pos - 1), color);
                    out = out.substr(pos + 1);
                }
            }

            // always ensure we still have place
            while (m_log.size() >= m_height - 1)
                m_log.erase(m_log.begin());
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
        void render_bar(int x, int y, int width, const std::string& name, float value, float max_val, const tcod::ColorRGB& fg, const tcod::ColorRGB& bg);

        void render_mouse_look(Engine* engine);

        struct Message {
            std::string text;
            tcod::ColorRGB color;
            Message(const std::string& text, const tcod::ColorRGB& color);
        };

        std::vector<Message> m_log;

        tcod::Console m_new_con;
        unsigned m_width, m_height;
        Proxy_t m_get_val;
    };
}

#endif
