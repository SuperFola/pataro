#ifndef PATARO_ACTION_HPP
#define PATARO_ACTION_HPP

#include <type_traits>
#include <memory>

namespace pat
{
    class Engine;

    /**
     * @brief The result of an action
     * 
     */
    enum class ActionResult
    {
        Success,
        Fail
    };

    /**
     * @brief Returned by an AI, contains the code which should be executed for a given turn
     * @details This class should be overriden, otherwise it does nothing by default.
     * 
     */
    class Action
    {
    public:
        /**
         * @brief Perform the action
         * 
         * @param engine 
         * @return ActionResult 
         */
        virtual ActionResult perform(Engine* engine);

        virtual ~Action() = default;

    protected:
        template <typename A, typename... Args>
        ActionResult alternate(Engine* engine, Args&&... args)
        {
            return A(std::forward<Args>(args)...).perform(engine);
        }
    };
}

#endif
