#include <Pataro/Animations/Frame.hpp>

#include <Pataro/Entity.hpp>

#include <utility>

using namespace pat::animation;

Frame::Frame(float duration, Frame::Op_t&& operation, bool is_loop) :
    m_duration(duration), m_operation(std::move(operation)),
    m_is_loop(is_loop)
{}

bool Frame::operator()(float dt, pat::Entity* source)
{
    m_elapsed += dt;

    if (!m_is_loop && m_elapsed >= m_duration)
    {
        m_operation(source);
        return true;
    }
    else if (m_is_loop)
        m_operation(source);

    return m_elapsed >= m_duration;
}