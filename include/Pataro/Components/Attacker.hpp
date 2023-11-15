#ifndef PATARO_COMPONENTS_ATTACKER_HPP
#define PATARO_COMPONENTS_ATTACKER_HPP

#include <memory>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class Attacker
    {
    public:
        /**
         * @brief Construct a new Attacker object
         * 
         * @param power 
         */
        explicit Attacker(float power);

        virtual ~Attacker() = default;

        [[nodiscard]] inline float power() const { return m_power; }

        [[nodiscard]] inline std::unique_ptr<Attacker> clone() const { return std::unique_ptr<Attacker>(clone_impl()); }

    protected:
        [[nodiscard]] virtual Attacker* clone_impl() const;

    private:
        float m_power;
    };
}

#endif
