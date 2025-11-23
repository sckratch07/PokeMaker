#ifndef _ENGINE_PHYSICSSYSTEM_HPP__
#define _ENGINE_PHYSICSSYSTEM_HPP__

/**
 * @file PhysicsSystem.hpp
 * @brief Définition du système PhysicsSystem.
 *
 * Ce système gère :
 * - le déplacement simple des entités
 * - la détection et résolution des collisions AABB
 *
 * Il utilise TransformComponent pour le positionnement
 * et CollisionComponent pour les boîtes de collision.
 */

#include "Engine/System.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Components/CollisionComponent.hpp"

namespace Engine
{
    /**
     * @class PhysicsSystem
     * @brief Système responsable de la gestion des collisions entre entités.
     *
     * Ce système effectue :
     * - l'avancement des entités (si un mouvement externe est appliqué)
     * - la détection des intersections entre boîtes de collision
     * - la résolution simple des collisions (séparation des entités)
     */
    class PhysicsSystem : public System
    {
    public:
        /**
         * @brief Met à jour toutes les entités concernées par la physique.
         *
         * @param registry Registry ENTt contenant entités et composants
         * @param dt Delta time écoulé depuis la dernière frame
         */
        void update(entt::registry& registry, float dt) override;

    private:
        /**
         * @brief Vérifie si deux AABB entrent en collision.
         *
         * @param a Première boîte de collision
         * @param b Seconde boîte de collision
         * @return true si les boîtes se chevauchent
         */
        bool intersects(const sf::FloatRect& a, const sf::FloatRect& b) const;
    };
}

#endif
