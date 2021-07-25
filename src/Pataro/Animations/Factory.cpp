#include <Pataro/Animations/Factory.hpp>

#include <Pataro/Entity.hpp>

using namespace pat::animation;

Factory::Factory()
{}

pat::Animation Factory::lightning_bolt(pat::Entity* target)
{
    return pat::Animation(target)
        .after(0.2f, [](pat::Entity* source){
            source->morph_into('7', TCODColor::lightBlue);
        })
        .after(0.2f, [](pat::Entity* source){
            source->morph_into('7', TCODColor::darkBlue);
        })
        .repeat(1)
        .revert();
}

pat::Animation Factory::burning(pat::Entity* target)
{
    return pat::Animation(target)
        .after(0.2f, [](pat::Entity* source){
            source->morph_into('w', TCODColor::orange);
        })
        .after(0.2f, [](pat::Entity* source){
            source->morph_into('W', TCODColor::darkOrange);
        })
        .repeat(1)
        .revert();
}