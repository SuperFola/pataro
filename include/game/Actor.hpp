#ifndef GAME_ACTOR_HPP
#define GAME_ACTOR_HPP

#include <libtcod.hpp>

class Actor
{
public:
    Actor(int x, int y, int ch, const TCODColor& color);
    void render() const;

private:
    int m_x;
    int m_y;
    int m_ch;
    TCODColor m_color;
};

#endif