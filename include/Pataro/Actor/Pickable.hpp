#ifndef PATARO_ACTOR_PICKABLE_HPP
#define PATARO_ACTOR_PICKABLE_HPP

namespace pat
{
    class Actor;
    class Engine;
}
namespace pat::actor
{
    class Pickable
    {
    public:
        /**
         * @brief Pick up an object
         * @details Check that the wearer has a container and tries to add the
         *          pickable to the wearer's container.
         * 
         * @param owner the object owning the pickable component
         * @param wearer the actor picking up the object
         * @param engine a pointer to the engine
         * @return true 
         * @return false 
         */
        bool pick(Actor* owner, Actor* wearer, Engine* engine);

        /**
         * @brief Use an object
         * 
         * @param owner the object owning the pickable component
         * @param wearer the actor picking up the object
         * @param engine a pointer to the engine
         * @return true 
         * @return false 
         */
        virtual bool use(Actor* owner, Actor* wearer, Engine* engine);

        /**
         * @brief Destroy the Pickable object
         * 
         */
        virtual ~Pickable() = default;
    };
}

#endif
