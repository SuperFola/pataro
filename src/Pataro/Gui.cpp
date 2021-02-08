#include <Pataro/Gui.hpp>

using namespace pat;

Gui::Gui(unsigned width, unsigned height, const Gui::Proxy_t& proxy, TCODConsole* destination) :
    m_width(width), m_height(height), m_get_val(proxy), m_dest(destination)
{
    m_con = std::make_unique<TCODConsole>(width, height);
}

void Gui::render()
{
    m_con->setDefaultBackground(TCODColor::black);
    m_con->clear();

    float val, max_val;
    m_get_val(&val, &max_val);

    render_bar(1, 1, 20, "HP", val, max_val, TCODColor::red, TCODColor::darkerRed);

    // TODO really really really temporayr because very ugly
    TCODConsole::blit(
        m_con.get(),
        0, 0,   // x_src, y_src
        m_width, m_height,  // w_src, h_src
        m_dest,
        0, 45 - m_height  //x_dst, y_dst
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
    m_con->print(
        x + width / 2, y,
        name + " : " + std::to_string(value) + "/" + std::to_string(max_val),
        TCOD_CENTER,
        TCOD_BKGND_NONE
    );
}