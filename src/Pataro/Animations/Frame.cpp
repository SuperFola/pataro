#include <Pataro/Animations/Frame.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>

#include <utility>

using namespace pat::animation;

Frame::Frame(float duration, Frame::Op_t&& operation, bool is_loop) :
    m_duration(duration), m_operation(std::move(operation)),
    m_is_loop(is_loop)
{}

bool Frame::operator()(float dt, pat::Entity* source, pat::Engine* engine)
{
    m_elapsed += dt;

    int dx = engine->get_player()->get_x() - engine->width()  / 2,
        dy = engine->get_player()->get_y() - engine->height() / 2;

    if (!m_is_loop && m_elapsed >= m_duration)
    {
        m_operation(source);
        source->render(dx, dy);
        return true;
    }
    else if (m_is_loop)
    {
        m_operation(source);
        source->render(dx, dy);
    }

    return m_elapsed >= m_duration;
}