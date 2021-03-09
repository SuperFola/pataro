#include <Pataro/Animation.hpp>

#include <Pataro/Entity.hpp>

using namespace pat;

Animation::Animation(Entity* source) :
    m_source(source), m_prev_ch(source->m_ch), m_prev_color(source->m_color)
{}

Animation& Animation::after(float duration, animation::Frame::Op_t&& operation)
{
    m_sequence.emplace_back(duration, std::move(operation));
    return *this;
}

Animation& Animation::repeat(std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i)
    {
        for (std::size_t c = 0, end = m_sequence.size(); c < end; ++c)
            m_sequence.push_back(m_sequence[c]);
    }
    return *this;
}

Animation& Animation::loop_for(float duration, animation::Frame::Op_t&& operation)
{
    m_sequence.emplace_back(duration, std::move(operation), /* is_loop */ true);
    return *this;
}

void Animation::update(float dt)
{
    // we have executed everything
    if (m_current >= m_sequence.size())
        return;

    if (m_sequence[m_current](dt, m_source))
        m_current++;

    if (is_finished())
        m_source->morph_into(m_prev_ch, m_prev_color);
}

bool Animation::is_finished() const
{
    return m_current >= m_sequence.size();
}