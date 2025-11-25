#ifndef _EDITOR_TILELAYER_HPP__
#define _EDITOR_TILELAYER_HPP__

/**
 * @file TileLayer.hpp
 * @brief Représente un layer de tiles : type, nom, grille de Tile.
 */

#include <string>
#include <vector>
#include <unordered_map>

#include <SFML/System/Vector2.hpp>

#include "Editor/Tile.hpp"

namespace Editor {

/**
 * @enum LayerType
 * @brief Définit le rôle d’un layer.
 */
enum class LayerType
{
    Ground,        ///< Sol (tiles principaux)
    Decoration,    ///< Décoration (arbres, murs…)
    Collision,     ///< Collision (masques)
    Overlay        ///< Au-dessus du joueur (toits, etc.)
};

/**
 * @class TileLayer
 * @brief Contient une grille 2D de Tile.
 *
 * Ce layer peut être sauvegardé via MapSerializer.
 */
class TileLayer
{
public:
    TileLayer();
    explicit TileLayer(const std::string& name,
                       LayerType type,
                       sf::Vector2u size);

    // ---- Métadonnées ----
    std::string name;
    LayerType type;
    sf::Vector2u size;

    // ---- Propriétés custom (ex: "shadow" = "true") ----
    std::unordered_map<std::string, std::string> properties;

    // ---- Grille de tiles ----
    std::vector<Tile> tiles;

    /// Renvoie un pointeur vers le tile (nullptr si out of bounds)
    Tile* GetTile(unsigned x, unsigned y);
    const Tile* GetTile(unsigned x, unsigned y) const;

    /// Change un tile (si position valide)
    void SetTile(unsigned x, unsigned y, const Tile& tile);

    /// Resize la grille (remplit de tiles vides)
    void Resize(sf::Vector2u newSize);

    /// Efface tous les tiles
    void Clear();

private:
    inline size_t Index(unsigned x, unsigned y) const
    {
        return y * size.x + x;
    }
};

} // namespace Editor

#endif // _EDITOR_TILELAYER_HPP__
