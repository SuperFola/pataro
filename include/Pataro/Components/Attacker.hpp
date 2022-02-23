#ifndef PATARO_COMPONENTS_ATTACKER_HPP
#define PATARO_COMPONENTS_ATTACKER_HPP

#include <cereal/types/memory.hpp>
#include <cereal/access.hpp>

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
        Attacker(float power);

        inline float power() const { return m_power; }

        inline std::unique_ptr<Attacker> clone() const { return std::unique_ptr<Attacker>(clone_impl()); }

        template <typename Archive>
        void save(Archive& archive) const
        {
            archive(cereal::make_nvp("Power", m_power));
        }

        template <typename Archive>
        void load(Archive& archive)
        {
            archive(m_power);
        }

        template <typename Archive>
        static void load_and_construct(Archive& archive, cereal::construct<Attacker>& construct)
        {
            archive(construct->m_power);
        }

    protected:
        virtual Attacker* clone_impl() const;

    private:
        float m_power;
    };
}

#endif
