#include <Pataro/Engine.hpp>

int main()
{
    pat::Engine engine(80, 45, "Pataro", /* show_debug */ true);

    while (engine.is_running())
    {
        engine.update();
        engine.render();

        TCODConsole::flush();
    }

    return 0;
}