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


namespace pat::component
{
    template <typename A, typename... Args>
    class OneTimeUse : public Use
    {
    public:
        using Callback_t = std::function<std::unique_ptr<Action>(Entity* source, Entity* owner)>;

        /**
         * @brief Construct a new One Time Use object, to launch an action taking a variadic number of arguments.
         * 
         * @param args 
         */
        OneTimeUse(Args&&... args)
        {
            m_function = [args = std::make_tuple(std::forward<Args>(args) ...)](Entity* source, Entity* owner) -> std::unique_ptr<Action> {
                return std::apply([source, owner](auto&&... args) {
                    return std::make_unique<A>(source, owner, args...);
                }, std::move(args));
            };
        }

    protected:
        std::unique_ptr<Action> use(Entity* source, Entity* owner, [[maybe_unused]] Engine* engine) override
        {
            return m_function(source, owner);
        }

        OneTimeUse<A, Args...>* clone_impl() const override
        {
            return new OneTimeUse<A, Args...>(m_function);
        }

    private:
        OneTimeUse(const Callback_t& callback) :
            m_function(callback)
        {}

        Callback_t m_function;
    };
}

#endif
