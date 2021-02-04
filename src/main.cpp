#include <Pataro/Engine.hpp>

int main()
{
    pat::Engine engine(80, 45, "Pataro");

    while (engine.is_running())
    {
        engine.update();
        engine.render();
    }

    return 0;
}