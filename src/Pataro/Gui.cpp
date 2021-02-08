#include <Pataro/Gui.hpp>

using namespace pat;

Gui::Gui(unsigned width, unsigned height, const Gui::Proxy_t& proxy) :
    m_width(width), m_height(height), m_get_val(proxy)
{
    m_con = std::make_unique<TCODConsole>(m_width, m_height);
}

void Gui::render(TCODConsole* dest, int x, int y)
{
    m_con->setDefaultBackground(TCODColor::black);
    m_con->clear();

    float val, max_val;
    m_get_val(&val, &max_val);

    render_bar({1, 1}, 20, "HP", val, max_val, TCODColor::red, TCODColor::darkerRed);

    TCODConsole::blit(
        m_con.get(),
        0, 0,   // x_src, y_src
        m_width, m_height,  // w_src, h_src
        dest,
        x, y  // x_dst, y_dst
    );
}

void Gui::render_bar(const Pos_t& pos, int width, const std::string& name, float value, float max_val, const TCODColor& fg, const TCODColor& bg)
{
    m_con->setDefaultBackground(bg);
    m_con->rect(pos.first, pos.second, width, 1, false, TCOD_BKGND_SET);

    int bar_width = static_cast<int>(value / max_val * width);
    if (bar_width > 0)
    {
        m_con->setDefaultBackground(fg);
        m_con->rect(pos.first, pos.second, bar_width, 1, false, TCOD_BKGND_SET);
    }

    m_con->setDefaultForeground(TCODColor::white);
    // FIXME it's given a warning
    m_con->printEx(
        pos.first + width / 2, pos.second,
        TCOD_BKGND_NONE,
        TCOD_CENTER,
        "%s : %g/%g", name.c_str(), value, max_val
    );
}