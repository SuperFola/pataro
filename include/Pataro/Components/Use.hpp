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
        /**
         * @brief Construct a new Use object
         * 
         * @param source the entity owning the component
         */
        Use(Entity* source);

        virtual ~Use() = default;

        /**
         * @brief The action it should perform
         * 
         * @param engine 
         * @return std::unique_ptr<Action> 
         */
        virtual std::unique_ptr<Action> operator()(Engine* engine);

        inline std::unique_ptr<Use> clone() const { return std::unique_ptr<Use>(clone_impl()); }

    protected:
        virtual Use* clone_impl() const;

    protected:
        Entity* m_source;
    };
}

#endif
