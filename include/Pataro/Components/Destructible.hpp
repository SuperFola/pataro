#ifndef PATARO_COMPONENTS_DESTRUCTIBLE_HPP
#define PATARO_COMPONENTS_DESTRUCTIBLE_HPP

#include <string>
#include <memory>
#include "cereal/types/memory.hpp"
#include <cereal/access.hpp>
#include <cereal/archives/xml.hpp>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class Destructible
    {
    public:
        /**
         * @brief Construct a new Destructible object
         * 
         * @param max_hp 
         * @param defense 
         * @param corpse_name the name of the Entity once dead
         */
        Destructible(float max_hp, float defense, const std::string& corpse_name);        

        /**
         * @brief Destroy the Destructible object
         * 
         */
        virtual ~Destructible() = default;

        /**
         * @brief Handles damages given to the destructible
         * 
         * @param owner 
         * @param damage 
         * @param engine 
         * @return float the number of hit points actually taken
         */
        float take_damage(Entity* owner, float damage, Engine* engine);

        /**
         * @brief What happens when the owning entity dies is handled here
         * 
         * @param owner 
         * @param engine 
         */
        virtual void die(Entity* owner, Engine* engine);

        /**
         * @brief Heals damages
         * 
         * @param amount 
         * @return float 
         */
        float heal(float amount);

        inline bool  is_dead() { return m_hp <= 0.f; }
        inline float max_hp()  { return m_max_hp; }
        inline float hp()      { return m_hp; }
        inline float defense() { return m_defense; }

        inline std::unique_ptr<Destructible> clone() const { return std::unique_ptr<Destructible>(clone_impl()); }

<<<<<<< Updated upstream
=======
        template<class Archive>
        void save(Archive& archive) const {
            archive(cereal::make_nvp("Max HP", m_max_hp), cereal::make_nvp("HP", m_hp),
                cereal::make_nvp("Defense", m_defense), cereal::make_nvp("CorpseName", m_corpse_name));
        }

        template<class Archive>
        void load(Archive& archive) {
            archive(m_max_hp, m_hp, m_defense, m_corpse_name);
        }

        template<class Archive>
        static void load_and_construct(Archive& archive, cereal::construct<Destructible>& construct) {
        archive(construct->m_max_hp, construct->m_hp, construct->m_defense, construct->m_corpse_name);         
        }

>>>>>>> Stashed changes
    protected:
        virtual Destructible* clone_impl() const;

    private:
        float m_max_hp, m_hp;
        float m_defense;
        std::string m_corpse_name;  ///< The Entity's name once dead
    };

    
}


#endif
