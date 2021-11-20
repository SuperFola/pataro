#include <Pataro/Engine.hpp>
#include <fstream>
#include "cereal/archives/xml.hpp"

int main()
{
    

    pat::Engine engine(80, 45, "Pataro", /* show_debug */ true);
    
    {   
        std::ifstream is("gameData.xml");

        if (is) {
            cereal::XMLInputArchive iarchive(is);
            iarchive(engine);
        }        
    

    while (engine.is_running())
    {
        engine.update();
        engine.render();

        TCODConsole::flush();
    }
    }
    {

        std::ofstream os("gameData.xml");
        cereal::XMLOutputArchive oarchive(os);
        oarchive(engine);        
    
    engine.export_log();
    }
    

    return 0;
}