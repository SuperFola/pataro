#include <Pataro/Animations/Factory.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Colors.hpp>

using namespace pat::animation;

Factory::Factory() :
    m_rng(TCODRandom::getInstance())
{}

pat::Animation Factory::lightning_bolt(pat::Entity* target)
{
    return pat::Animation(target)
        .after(0.2f, [](pat::Entity* source){
            source->morph_into('7', colors::lightBlue);
        })
        .after(0.2f, [](pat::Entity* source){
            source->morph_into('7', colors::darkBlue);
        })
        .repeat(1)
        .revert();
}

pat::Animation Factory::burning(pat::Entity* target)
{
    return pat::Animation(target)
        .after(0.2f, [](pat::Entity* source){
            source->morph_into('w', colors::orange);
        })
        .after(0.2f, [](pat::Entity* source){
            source->morph_into('W', colors::darkOrange);
        })
        .repeat(1)
        .revert();
}