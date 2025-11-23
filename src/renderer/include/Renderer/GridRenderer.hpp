#ifndef _RENDERER_GRIDRENDERER_HPP__
#define _RENDERER_GRIDRENDERER_HPP__

#include "Renderer/Renderer.hpp"
#include <SFML/Graphics/VertexArray.hpp>

namespace Renderer
{

    /**
     * @class GridRenderer
     * @brief Système permettant d'afficher une grille en superposition.
     *
     * La grille est principalement utilisée dans l'éditeur pour aider
     * à visualiser la map, placer des tuiles et aligner les éléments.
     */
    class GridRenderer
    {
    public:
        /**
         * @brief Constructeur.
         *
         * @param renderer Renderer principal utilisé pour le dessin.
         */
        GridRenderer(Renderer& renderer);

        /**
         * @brief Configure la grille.
         *
         * @param cellSize Taille d'une cellule en pixels.
         * @param width Nombre de cellules horizontalement.
         * @param height Nombre de cellules verticalement.
         */
        void configure(int cellSize, int width, int height);

        /**
         * @brief Dessine la grille dans la scène.
         */
        void draw();

    private:
        Renderer& m_renderer; ///< Renderer principal.

        sf::VertexArray m_vertices; ///< Ensemble des lignes de la grille.

        int m_cellSize = 32; ///< Taille d’une cellule.
        int m_width = 0;     ///< Nombre de cellules (X).
        int m_height = 0;    ///< Nombre de cellules (Y).
    };

} // namespace Renderer

#endif
