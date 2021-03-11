#include <Pataro/Animations/Factory.hpp>

#include <Pataro/Entity.hpp>

using namespace pat::animation;

Factory::Factory() :
    m_rng(TCODRandom::getInstance())
{}

pat::Animation Factory::lightningBolt(pat::Entity* target)
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