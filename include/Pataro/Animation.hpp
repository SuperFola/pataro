#ifndef PATARO_ANIMATION_HPP
#define PATARO_ANIMATION_HPP

#include <Pataro/Animations/Frame.hpp>

#include <vector>

#include <libtcod.hpp>

namespace pat
{
    class Entity;

    class Animation
    {
    public:
        /**
         * @brief Construct a new Animation object
         * 
         * @param source the entity to which the animation should be applied
         */
        Animation(Entity* source);

        /**
         * @brief Add a frame, after a given duration, executes once the given operation
         * 
         * @param duration 
         * @param operation 
         * @return Animation& 
         */
        Animation& after(float duration, animation::Frame::Op_t&& operation);

        /**
         * @brief Repeat all the previous registered frames by a given number
         * 
         * @param count 
         * @return Animation& 
         */
        Animation& repeat(std::size_t count);

        /**
         * @brief Execute the given operation at every tick of the game, for a given duration
         * 
         * @param duration 
         * @param operation 
         * @return Animation& 
         */
        Animation& loop_for(float duration, animation::Frame::Op_t&& operation);

        /**
         * @brief Revert modifications to the entities to the state it had when the animation was created
         * 
         * @return Animation& 
         */
        Animation& revert();

        /**
         * @brief Run the animation
         * 
         * @param dt 
         */
        void update(float dt);

        /**
         * @brief Check if the animation is finished or not
         * 
         * @return true 
         * @return false 
         */
        bool is_finished() const;

    private:
        std::size_t m_current = 0;
        std::vector<animation::Frame> m_sequence;
        Entity* m_source;

        int m_prev_ch;
        TCODColor m_prev_color;
    };
}

#endif
