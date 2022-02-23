#include <Pataro/Engine.hpp>
#include <fstream>
#include <cereal/archives/xml.hpp>

int main()
{
    pat::Engine engine(80, 45, "Pataro", /* show_debug */ true);

    // load the save if it exists
    if (std::ifstream game_data("gameData.xml"); game_data.good()) {
        cereal::XMLInputArchive archive(game_data);
        archive(engine);
    }

    while (engine.is_running())
    {
        engine.update();
        engine.render();

        TCODConsole::flush();
    }

    // write save data
    std::ofstream os("gameData.xml");
    cereal::XMLOutputArchive archive(os);
    archive(engine);

    engine.export_log();

    return 0;
}