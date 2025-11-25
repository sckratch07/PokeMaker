#ifndef _EDITOR_AUTOTILE_HPP__
#define _EDITOR_AUTOTILE_HPP__

/**
 * @file AutoTile.hpp
 * @brief Système d'autotile basé sur un masque 8 directions configurable par l'utilisateur.
 *
 * L'utilisateur fournit une table :
 *    mask (0-255) -> tileId
 *
 * Le mask est composé comme suit (8 directions) :
 *
 *        128 | 1 | 2
 *        64  | X | 4
 *        32  |16 | 8
 *
 * Bit mapping :
 *  1   = North
 *  2   = North-East
 *  4   = East
 *  8   = South-East
 *  16  = South
 *  32  = South-West
 *  64  = West
 *  128 = North-West
 */

#include <unordered_map>
#include <cstdint>
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace Editor {

class TileLayer;

/**
 * @struct AutoTileRule
 * @brief Définit une règle simple : mask -> tileId
 */
struct AutoTileRule
{
    uint8_t mask;
    uint32_t tileId;
};

/**
 * @class AutoTile
 * @brief Gère l'application du système d'autotile.
 */
class AutoTile
{
public:
    AutoTile() = default;

    /// Définit ou redéfinit une règle d'autotile
    void SetRule(uint8_t mask, uint32_t tileId);

    /// Supprime une règle
    void RemoveRule(uint8_t mask);

    /// Efface toutes les règles
    void Clear();

    /// Applique l'autotile sur une position du layer
    void ApplyToTile(TileLayer& layer, unsigned x, unsigned y);

    /// Applique l'autotile à tout le layer
    void ApplyToLayer(TileLayer& layer);

    /// Renvoie la règle associée à un mask (ou 0 s'il n'y en a pas)
    uint32_t Resolve(uint8_t mask) const;

    /// Génère le mask 8 directions pour la position donnée
    uint8_t ComputeMask(const TileLayer& layer, unsigned x, unsigned y) const;

    /// Récupérer toutes les règles (pour UI ou JSON)
    const std::unordered_map<uint8_t, uint32_t>& GetRules() const { return m_rules; }

private:
    std::unordered_map<uint8_t, uint32_t> m_rules;
};

} // namespace Editor

#endif // _EDITOR_AUTOTILE_HPP__
