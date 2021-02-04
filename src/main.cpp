#include <libtcod.hpp>

int main()
{
    int x = 40, y = 25;

    TCODConsole::initRoot(80, 50, "libtcod C++ tutorial", false);
    while (!TCODConsole::isWindowClosed())
    {
        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
        switch (key.vk)
        {
            case TCODK_UP: y--; break;
            case TCODK_DOWN: y++; break;
            case TCODK_LEFT: x--; break;
            case TCODK_RIGHT: x++; break;
        }
        TCODConsole::root->clear();
        TCODConsole::root->putChar(x, y, '@');
        TCODConsole::flush();
   }

    return 0;
}