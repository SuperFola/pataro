#ifndef PATARO_ANIMATIONS_FRAME_HPP
#define PATARO_ANIMATIONS_FRAME_HPP

#include <functional>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::animation
{
    class Frame
    {
    public:
        using Op_t = std::function<void(Entity*)>;

        /**
         * @brief Construct a new Frame object
         * 
         * @param duration 
         * @param operation 
         * @param is_loop default: false
         */
        Frame(float duration, Op_t&& operation, bool is_loop = false);

        /**
         * @brief Execute the frame
         * 
         * @param dt 
         * @param source 
         * @param engine 
         * @return true if the animation is finally done
         * @return false if it should remain the current frame
         */
        bool operator()(float dt, Entity* source, Engine* engine);

    private:
        float m_duration;
        Op_t m_operation;
        bool m_is_loop;

        float m_elapsed = 0.f;
    };
}

#endif
