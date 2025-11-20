#ifndef _ENGINE_SPRITECOMPONENT_HPP__
#define _ENGINE_SPRITECOMPONENT_HPP__

/**
 * @file SpriteComponent.hpp
 * @brief Définition du composant SpriteComponent.
 *
 * Ce composant permet d'associer une texture et un sprite SFML à une entité.
 * Il est généralement utilisé avec TransformComponent pour l'affichage.
 */

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Engine
{
    /**
     * @struct SpriteComponent
     * @brief Composant gérant l'affichage d'un sprite.
     *
     * Il contient :
     * - un pointeur vers une texture (géré ailleurs par un ResourceManager)
     * - un sprite SFML prêt à être manipulé
     *
     * Le sprite n’est pas mis à jour automatiquement : un système (ex : RenderSystem)
     * doit s'occuper de synchroniser la position avec TransformComponent.
     */
    struct SpriteComponent
    {
        const sf::Texture* texture = nullptr; ///< Texture utilisée par le sprite
        sf::Sprite sprite;                    ///< Instance du sprite affichable
    };
}

#endif
