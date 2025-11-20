#ifndef _ENGINE_COLLISIONCOMPONENT_HPP__
#define _ENGINE_COLLISIONCOMPONENT_HPP__

/**
 * @file CollisionComponent.hpp
 * @brief Définition du composant CollisionComponent.
 *
 * Ce composant décrit une boîte de collision rectangulaire (AABB) associée
 * à une entité.  
 * Il est généralement utilisé avec TransformComponent pour déterminer la
 * position et avec PhysicsSystem pour gérer les interactions.
 */

#include <SFML/Graphics/Rect.hpp>

namespace Engine
{
    /**
     * @struct CollisionComponent
     * @brief Composant représentant une boîte de collision axis-aligned (AABB).
     *
     * La boîte est exprimée en coordonnées locales :  
     * elle sera ensuite déplacée en fonction du TransformComponent
     * par les systèmes de physique ou de collision.
     */
    struct CollisionComponent
    {
        sf::FloatRect bounds; ///< Boîte de collision locale, définie par (x, y, width, height)
        bool isSolid = true;  ///< Si vrai, l'entité bloque les autres entités lors des collisions
    };
}

#endif
