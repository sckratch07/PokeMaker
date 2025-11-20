#ifndef _ENGINE_ANIMATIONCOMPONENT_HPP__
#define _ENGINE_ANIMATIONCOMPONENT_HPP__

/**
 * @file AnimationComponent.hpp
 * @brief Définition du composant AnimationComponent.
 *
 * Ce composant gère une animation image-par-image (frame-based), généralement
 * utilisée avec un SpriteComponent.  
 * Il stocke :
 * - une liste de frames (rectangles dans une texture)
 * - la durée d'affichage de chaque frame
 * - l'état interne de lecture (frame actuelle, timer)
 */

#include <SFML/Graphics/Rect.hpp>
#include <vector>

namespace Engine
{
    /**
     * @struct AnimationComponent
     * @brief Composant permettant d'animer un sprite en changeant régulièrement son rectangle de texture.
     */
    struct AnimationComponent
    {
        std::vector<sf::IntRect> frames; ///< Liste des frames de l'animation dans la texture
        float frameTime = 0.1f;          ///< Durée d'affichage d'une frame (en secondes)
        bool loop = true;                ///< Indique si l'animation revient à la première frame quand elle se termine

        // État interne géré par AnimationSystem
        std::size_t currentFrame = 0;    ///< Frame actuellement affichée
        float timer = 0.f;               ///< Temps écoulé depuis le changement de frame

        /**
         * @brief Vérifie si l'animation possède des frames valides.
         * @return True si au moins une frame est disponible.
         */
        bool isValid() const
        {
            return !frames.empty();
        }
    };
}

#endif
