#ifndef _CORE_ENTITYMANAGER_HPP__
#define _CORE_ENTITYMANAGER_HPP__

#include <entt/entt.hpp>

namespace Core
{
    /**
    * @brief Wrapper du registry EnTT.
    *
    * L'EntityManager centralise l'accès à EnTT afin de :
    * - Découpler le reste du moteur de la librairie EnTT
    * - Offrir une API claire et documentée
    * - Faciliter la sérialisation (JSON) des entités
    *
    * Il est utilisé aussi bien par :
    * - l'éditeur (création NPC, joueur, objets)
    * - le runtime du jeu
    */
    class EntityManager
    {
    public:
        /**
        * @brief Constructeur
        */
        EntityManager() = default;

        /**
        * @brief Destructeur
        */
        ~EntityManager() = default;

        /**
        * @brief Crée une nouvelle entité
        * @return Identifiant EnTT de l'entité
        */
        entt::entity createEntity();

        /**
        * @brief Détruit une entité
        * @param entity Entité à détruire
        */
        void destroyEntity(entt::entity entity);

        /**
        * @brief Supprime toutes les entités
        */
        void clear();

        /**
        * @brief Accès direct au registry EnTT
        *
        * À utiliser avec parcimonie.
        */
        entt::registry& registry();

        /**
        * @brief Accès constant au registry EnTT
        */
        const entt::registry& registry() const;

    private:
        entt::registry m_registry; /**< Registry EnTT central */
    };
}

#endif // _CORE_ENTITYMANAGER_HPP__