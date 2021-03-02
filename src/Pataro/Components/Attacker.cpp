#include <Pataro/Components/Attacker.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat::component;

Attacker::Attacker(float power) :
    m_power(power)
{}