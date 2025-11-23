#ifndef _RENDERER_TILERENDERER_HPP__
#define _RENDERER_TILERENDERER_HPP__

#include "Renderer/Renderer.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Renderer
{

    /**
     * @class TileRenderer
     * @brief Système de rendu chargé d'afficher des tuiles 2D.
     *
     * Cette classe utilise le Renderer principal pour afficher des sprites
     * représentant des tuiles d'un tileset. Elle est pensée pour être
     * utilisée par l'éditeur ainsi que par le jeu final.
     */
    class TileRenderer
    {
    public:
        /**
         * @brief Constructeur du TileRenderer.
         *
         * @param renderer Référence vers le Renderer principal utilisé pour le rendu.
         */
        TileRenderer(Renderer& renderer);

        /**
         * @brief Définit la texture utilisée comme tileset.
         *
         * @param texture Référence à la texture contenant les tuiles.
         * @param tileWidth Largeur d'une tuile en pixels.
         * @param tileHeight Hauteur d'une tuile en pixels.
         */
        void setTileset(const sf::Texture& texture, int tileWidth, int tileHeight);

        /**
         * @brief Rendu d'une tuile à une position donnée dans le monde.
         *
         * @param tileIndex Index de la tuile dans le tileset.
         * @param x Position X en pixels.
         * @param y Position Y en pixels.
         */
        void drawTile(int tileIndex, float x, float y);

    private:
        Renderer& m_renderer;         ///< Renderer principal.
        const sf::Texture* m_tileset; ///< Texture contenant les tuiles.

        int m_tileWidth = 0;  ///< Largeur d'une tuile.
        int m_tileHeight = 0; ///< Hauteur d'une tuile.
    };

} // namespace Renderer

#endif
