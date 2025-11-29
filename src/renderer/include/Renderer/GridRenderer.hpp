#ifndef _RENDERER_GRIDRENDERER_HPP__
#define _RENDERER_GRIDRENDERER_HPP__

#include <SFML/Graphics.hpp>

namespace Renderer
{
/**
* @brief Dessine une grille et des overlays (sélection, surlignage de tile).
*
* Composant utile à l'Editor mais qui peut aussi être utilisé en débogage dans
* Game. Ne dépend pas de Core.
*/
class GridRenderer
{
public:
    GridRenderer();

    /**
    * @brief Définit la taille d'une case en pixels et la taille totale (en tiles).
    */
    void SetGridSize(int tileWidth, int tileHeight, int tilesX, int tilesY) noexcept;

    /**
    * @brief Définit la vue (pour savoir quelle portion dessiner).
    */
    void SetView(const sf::View& view) noexcept;

    /**
    * @brief Dessine la grille et l'overlay de sélection.
    * @param target la cible de rendu
    * @param selection Rect en coordonnées tiles (x,y,w,h). Si width ou height = 0, rien n'est dessiné.
    */
    void Draw(sf::RenderTarget& target, const sf::IntRect& selection = sf::IntRect()) const;

private:
    int m_tileWidth = 32;
    int m_tileHeight = 32;
    int m_tilesX = 0;
    int m_tilesY = 0;
    sf::View m_view;
};
} // namespace renderer

#endif