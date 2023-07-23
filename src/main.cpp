#include <Pataro/Engine.hpp>
#include <Pataro/Config.hpp>

int main()
{
    pat::Config conf {
        .themes = {{
            pat::Config::Theme {
                .wall = pat::Config::Tile {
                    .repr = ' ',
                    .color_visible = tcod::ColorRGB(130, 110, 50),
                    .color_outside_fov = tcod::ColorRGB(0, 0, 100)
                },
                .ground = pat::Config::Tile {
                    .repr = ' ',
                    .color_visible = tcod::ColorRGB(200, 180, 50),
                    .color_outside_fov = tcod::ColorRGB(50, 50, 150)
                }
            }
        }}
    };
    pat::Engine engine(80, 45, "Pataro", conf, /* show_debug */ true);

    while (engine.is_running())
    {
        engine.update();
        engine.render();
        engine.flush();
    }

    engine.export_log();

    return 0;
}