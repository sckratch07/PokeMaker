#ifndef _EDITOR_AUTOTILE_HPP__
#define _EDITOR_AUTOTILE_HPP__

/**
 * @file AutoTile.hpp
 * @brief Algorithme simple d'auto-tiling basé sur bitmask (8-voisins).
 *
 * AutoTile ne dessine pas lui-même : il calcule un "variant index" en fonction
 * des voisins et renvoie un index de tile à utiliser.
 */

#include <array>
#include <cstdint>
#include <vector>
#include "Editor/Map/Tile.hpp"

namespace Editor::Map {

/**
 * @class AutoTile
 * @brief Gère une table de variantes pour un tile auto.
 *
 * - mapping : vecteur de tileIndex (dans le tileset) indexé par bitmask (0..255)
 * - computeVariant(neighbors) : calcule bitmask et retourne tileIndex
 *
 * Note : neighbors doit être fourni sous la forme d'un tableau bool[8] (N, NE, E, SE, S, SW, W, NW)
 */
class AutoTile
{
public:
    AutoTile() = default;

    /// Définit le mapping bitmask->tileIndex ; mapping[i] correspond au tileIndex à utiliser pour bitmask i
    void SetMapping(const std::vector<int>& mapping);

    /// Retourne le tileIndex correspondant aux voisins fournis (si mapping est vide retourne -1)
    int ComputeVariant(const std::array<bool,8>& neighbors) const;

    /// Utilitaire : génère un bitmask (0..255) depuis neighbors
    static uint8_t ComputeBitmask(const std::array<bool,8>& neighbors);

    /// Retourne vrai si une mapping est définie
    bool HasMapping() const;

private:
    std::vector<int> m_mapping; // size up to 256
};

} // namespace Editor::Map

#endif // _EDITOR_AUTOTILE_HPP__
