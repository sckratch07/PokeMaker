#ifndef _ENGINE_BEHAVIORSYSTEM_HPP__
#define _ENGINE_BEHAVIORSYSTEM_HPP__

/**
 * @file BehaviorSystem.hpp
 * @brief Définition du système BehaviorSystem.
 *
 * Ce système applique la logique de comportement (IA simple) aux entités
 * possédant un BehaviorComponent.  
 * Il peut agir sur :
 * - TransformComponent (déplacements)
 * - NPCComponent (interaction ou logique PNJ)
 *
 * Le système est conçu pour être facilement étendu.
 */

#include "Engine/System.hpp"
#include "Engine/Components/BehaviorComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Components/NPCComponent.hpp"

#include <SFML/System/Vector2.hpp>

namespace Engine
{
    /**
     * @class BehaviorSystem
     * @brief Système gérant les comportements IA des entités.
     *
     * Les comportements supportés :
     * - Idle   : aucune action
     * - Wander : déplacement aléatoire simple
     * - Follow : déplacement vers une cible
     * - Custom : laissé à l'utilisateur
     */
    class BehaviorSystem : public System
    {
    public:
        /**
         * @brief Met à jour la logique de comportement.
         *
         * @param registry Registry ENTt contenant les entités et composants
         * @param dt Delta time en secondes depuis la dernière frame
         */
        void update(entt::registry& registry, float dt) override;

    private:
        /**
         * @brief Applique un léger déplacement aléatoire (IA Wander).
         */
        void applyWander(TransformComponent& transform, BehaviorComponent& behavior, float dt);

        /**
         * @brief Fait suivre une cible (IA Follow).
         */
        void applyFollow(entt::registry& registry, TransformComponent& transform, BehaviorComponent& behavior, float dt);
    };
}

#endif
