#ifndef _ENGINE_TRANSFORMCOMPONENT_HPP__
#define _ENGINE_TRANSFORMCOMPONENT_HPP__

/**
 * @file TransformComponent.hpp
 * @brief Définition du composant TransformComponent.
 *
 * Le TransformComponent représente la position, l'échelle et la rotation
 * d'une entité dans le monde du jeu.  
 * Il constitue un des composants fondamentaux dans un moteur ECS.
 */

#include <SFML/System/Vector2.hpp>

namespace Engine
{
    /**
     * @struct TransformComponent
     * @brief Composant représentant la transformation d'une entité.
     *
     * Il contient :
     * - une position (x, y)
     * - une échelle (scaleX, scaleY)
     * - une rotation (en degrés)
     */
    struct TransformComponent
    {
        sf::Vector2f position {0.f, 0.f}; ///< Position de l'entité dans le monde
        sf::Vector2f scale {1.f, 1.f};    ///< Facteur d'échelle de l'entité
        float rotation = 0.f;             ///< Rotation de l'entité (en degrés)
    };
}

#endif
