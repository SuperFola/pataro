#ifndef COMPONENTS_USE_ONETIME_HPP
#define COMPONENTS_USE_ONETIME_HPP

#include <Pataro/Action.hpp>
#include <Pataro/Components/Use.hpp>

#include <memory>
#include <utility>
#include <functional>


namespace pat
{
    class Entity;
    class Engine;
}


namespace pat::component::details
{
    template <typename A, typename T>
    class OneTimeUse : public Use
    {
    public:
        /**
         * @brief Construct a new One Time Use object, to launch an action taking a single argument
         * 
         * @param data 
         */
        OneTimeUse(T data) :
            m_data(data)
        {
            m_action = [this](Entity* source, Entity* owner) -> std::unique_ptr<Action> {
                return std::make_unique<A>(source, owner, m_data);
            };
        }

    protected:
        std::unique_ptr<Action> use(Entity* source, Entity* owner, [[maybe_unused]] Engine* engine) override
        {
            return m_action(source, owner);
        }

        OneTimeUse* clone_impl() const override
        {
            return new OneTimeUse<A, T>(m_data);
        }

    private:
        std::function<std::unique_ptr<Action>(Entity* source, Entity* owner)> m_action;
        T m_data;
    };
}

#endif
