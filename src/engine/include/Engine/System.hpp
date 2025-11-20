#ifndef _ENGINE_SYSTEM_HPP__
#define _ENGINE_SYSTEM_HPP__

/**
 * @file System.hpp
 * @brief Définition de la classe abstraite System, base de tous les systèmes du moteur ECS.
 *
 * La classe System représente une unité logique appliquant une mise à jour
 * sur un sous-ensemble d'entités possédant certains composants.  
 * Tous les systèmes spécialisés (physique, animation, comportement…) héritent de cette classe.
 */

#include <entt/entt.hpp>

namespace Engine
{
    /**
     * @class System
     * @brief Classe de base abstraite représentant un système ECS.
     *
     * Un système agit sur les entités possédant un ensemble défini de composants.
     * Chaque système doit implémenter la méthode update().
     */
    class System
    {
    public:
        /**
         * @brief Constructeur par défaut.
         */
        System() = default;

        /**
         * @brief Destructeur virtuel pour un comportement polymorphique.
         */
        virtual ~System() = default;

        /**
         * @brief Met à jour le système.
         *
         * @param registry Référence vers l'enregistreur ENTt contenant toutes les entités et leurs composants.
         * @param dt Delta time (en secondes) depuis la dernière frame.
         *
         * Cette fonction est appelée à chaque frame par World.
         */
        virtual void update(entt::registry& registry, float dt) = 0;
    };
}

#endif
