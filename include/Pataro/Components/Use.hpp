#ifndef PATARO_COMPONENTS_USE_HPP
#define PATARO_COMPONENTS_USE_HPP

#include <Pataro/Action.hpp>

#include <memory>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class Use
    {
    public:
        virtual ~Use() = default;

        /**
         * @brief Use the component if we can. First, checks if it was destroyed or not
         * 
         * @param source 
         * @param owner the owner of the source object we are using
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        std::unique_ptr<Action> perform(Entity* source, Entity* owner, Engine* engine);

        /**
         * @brief Remove from container
         * 
         */
        void remove_from_container(Entity* owner, Entity* source);

        inline std::unique_ptr<Use> clone() const { return std::unique_ptr<Use>(clone_impl()); }

    protected:
        /**
         * @brief The action it should perform
         * @details Must be implemented by the end user
         * 
         * @param source 
         * @param owner the owner of the source object we are using
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        virtual std::unique_ptr<Action> use(Entity* source, Entity* owner, Engine* engine) = 0;

        virtual Use* clone_impl() const = 0;

    private:
        bool m_destroyed = false;  ///< When equal to true, can not use it again
    };
}

#endif
