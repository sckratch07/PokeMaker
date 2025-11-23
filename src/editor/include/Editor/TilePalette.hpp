#ifndef _EDITOR_TILEPALETTE_HPP__
#define _EDITOR_TILEPALETTE_HPP__

/**
 * @file TilePalette.hpp
 * @brief Palette de tuiles : chargement, affichage et sélection.
 *
 * Permet de charger un atlas de tuiles et de sélectionner une tuile pour peindre.
 * Fournit des accesseurs pour permettre l'intégration (affichage, règles WFC...).
 */

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace Editor {

/**
 * @class TilePalette
 * @brief Gère un atlas de tuiles et l'interface de sélection.
 */
class TilePalette
{
public:
    TilePalette();
    ~TilePalette();

    /**
     * @brief Charge une texture d'atlas depuis un fichier.
     * @param path Chemin vers l'image.
     * @param tileWidth Largeur d'une tuile.
     * @param tileHeight Hauteur d'une tuile.
     * @param spacing Espacement entre tuiles (optionnel).
     * @return true si succès.
     */
    bool loadFromFile(const std::string& path, int tileWidth, int tileHeight, int spacing = 0);

    /** @brief Affiche la palette dans ImGui. */
    void render();

    /** @brief Obtient l'indice de la tuile sélectionnée (-1 si aucune). */
    int selectedTile() const;

    /** ----------------- NOUVEAUX ACCESSEURS ----------------- */

    /**
     * @brief Retourne un pointeur vers la texture SFML (peut être nullptr si non chargée).
     */
    const sf::Texture* texture() const;

    /**
     * @brief Retourne la liste des rectangles de tuiles (IntRect) dans l'atlas.
     */
    const std::vector<sf::IntRect>& tiles() const;

    /**
     * @brief Nombre de tuiles disponibles dans l'atlas.
     */
    int tileCount() const;

private:
    sf::Texture m_texture;
    int m_tileWidth;
    int m_tileHeight;
    int m_spacing;
    int m_selected;
    std::vector<sf::IntRect> m_tiles;
};

} // namespace Editor

#endif
