#ifndef _ENGINE_TILECOMPONENT_HPP__
#define _ENGINE_TILECOMPONENT_HPP__

/**
 * @file TileComponent.hpp
 * @brief Définition du composant TileComponent.
 *
 * Ce composant représente une tuile (tile) provenant d'un tileset.
 * Il contient les informations nécessaires pour dessiner une tuile statique :
 * - un rectangle source dans la texture
 * - un identifiant de tileset
 */

#include <SFML/Graphics/Rect.hpp>
#include <string>

namespace Engine
{
    /**
     * @struct TileComponent
     * @brief Composant représentant une tuile d’un tileset.
     *
     * Il est généralement utilisé dans les cartes 2D composées de tuiles.
     */
    struct TileComponent
    {
        std::string tilesetName;   ///< Nom ou identifiant du tileset utilisé
        sf::IntRect textureRect;   ///< Portion de la texture correspondant à la tuile
    };
}

#endif
