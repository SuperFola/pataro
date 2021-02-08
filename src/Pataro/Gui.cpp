#include <Pataro/Gui.hpp>

using namespace pat;

Gui::Gui(unsigned width, unsigned height, const Gui::Proxy_t& proxy) :
    m_width(width), m_height(height), m_get_val(proxy)
{
    m_con = std::make_unique<TCODConsole>(m_width, m_height);
}

void Gui::render(TCODConsole* dest, int x, int y)
{
    // TODO put this elsewhere
    static const int bar_width = 20;

    m_con->setDefaultBackground(TCODColor::black);
    m_con->clear();

    float val, max_val;
    m_get_val(&val, &max_val);
    render_bar(1, 1, bar_width, "HP", val, max_val, TCODColor::red, TCODColor::darkerRed);

    int msg_y = 1;
    float color_coeff = 0.4f;
    for (const Message& msg : m_log)
    {
        m_con->setDefaultForeground(msg.color * color_coeff);
        m_con->printf(bar_width + 2, msg_y, TCOD_BKGND_NONE, TCOD_LEFT, msg.text.c_str());

        ++msg_y;
        if (color_coeff < 1.f)
            color_coeff += 0.2f;
    }

    TCODConsole::blit(
        m_con.get(),
        0, 0,   // x_src, y_src
        m_width, m_height,  // w_src, h_src
        dest,
        x, y  // x_dst, y_dst
    );
}

void Gui::render_bar(int x, int y, int width, const std::string& name, float value, float max_val, const TCODColor& fg, const TCODColor& bg)
{
    m_con->setDefaultBackground(bg);
    m_con->rect(x, y, width, 1, false, TCOD_BKGND_SET);

    int bar_width = static_cast<int>(value / max_val * width);
    if (bar_width > 0)
    {
        m_con->setDefaultBackground(fg);
        m_con->rect(x, y, bar_width, 1, false, TCOD_BKGND_SET);
    }

    m_con->setDefaultForeground(TCODColor::white);
    m_con->printf(
        x + width / 2, y,
        TCOD_BKGND_NONE, TCOD_CENTER,
        "%s : %g/%g", name.c_str(), value, max_val
    );
}

Gui::Message::Message(const std::string& text_, const TCODColor& color_) :
    text(text_), color(color_)
{}