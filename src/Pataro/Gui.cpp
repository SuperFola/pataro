#include <Pataro/Gui.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Colors.hpp>

using namespace pat;

Gui::Gui(unsigned width, unsigned height, const Gui::Proxy_t& proxy) :
    m_new_con(width, height), m_width(width), m_height(height), m_get_val(proxy)
{}

void Gui::render(Engine* engine, TCOD_Console* dest, int x, int y)
{
    // TODO put this bar_width elsewhere
    static const int bar_width = 20;

    m_new_con.clear({' ', colors::black, colors::black});

    float val, max_val;
    m_get_val(&val, &max_val);
    render_bar(1, 1, bar_width, "HP", val, max_val, colors::red, colors::darkRed);

    int msg_y = 1;
    float color_coeff = 0.4f;
    for (const Message& msg : m_log)
    {
        //m_con->setDefaultForeground(msg.color * color_coeff);
        //m_con->printf(bar_width + 2, msg_y, msg.text.c_str());

        tcod::ColorRGB fg = {
            static_cast<uint8_t>(msg.color.r * color_coeff),
            static_cast<uint8_t>(msg.color.g * color_coeff),
            static_cast<uint8_t>(msg.color.b * color_coeff)
        };
        tcod::print(m_new_con, {bar_width + 2, msg_y}, msg.text, fg, std::nullopt);

        ++msg_y;
        if (color_coeff < 1.f)
            color_coeff += 0.2f;
    }

    render_mouse_look(engine);

    tcod::blit(*dest, *m_new_con.get(), {x, y});
}

void Gui::render_bar(int x, int y, int width, const std::string& name, float value, float max_val, const tcod::ColorRGB& fg, const tcod::ColorRGB& bg)
{
    tcod::draw_rect(m_new_con, {x, y, width, 1}, 0, std::nullopt, bg);

    int bar_width = static_cast<int>(value / max_val * width);
    if (bar_width > 0)
    {
        tcod::draw_rect(m_new_con, {x, y, bar_width, 1}, 0, std::nullopt, fg);
    }

    tcod::print(m_new_con, {x + width / 2, y}, tcod::stringf("%s : %g/%g", name.c_str(), value, max_val), colors::white, std::nullopt, TCOD_CENTER, TCOD_BKGND_NONE);
}

void Gui::render_mouse_look(Engine* engine)
{
    const TCOD_mouse_t& mouse = engine->mouse();
    int x = mouse.cx + (engine->get_player()->get_x() - engine->width() / 2),
        y = mouse.cy + (engine->get_player()->get_y() - engine->height() / 2);

    // no rendering needed if the mouse is out of the fov
    if (!engine->get_map()->is_in_fov(x, y))
        return;

    std::string text = "";
    bool first = true;
    for (const auto& entity : engine->get_map()->current_level().get_entities())
    {
        if (entity->get_x() == x && entity->get_y() == y)
        {
            if (!first)
                text += ", ";
            else
                first = false;
            text += entity->get_name();
        }
    }

    tcod::print(m_new_con, {1, 0}, text, colors::lightGrey, std::nullopt);
}

Gui::Message::Message(const std::string& text_, const tcod::ColorRGB& color_) :
    text(text_), color(color_)
{}
