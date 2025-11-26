#ifndef _EDITOR_ANIMATEDTILE_HPP__
#define _EDITOR_ANIMATEDTILE_HPP__

/**
 * @file AnimatedTile.hpp
 * @brief Tile animée composée d'une séquence de frames (chaque frame est une Tile).
 */

#include "Editor/Map/Tile.hpp"
#include <vector>

namespace Editor::Map {

/**
 * @class AnimatedTile
 * @brief Représente une tile animée (séquence de frames).
 *
 * Fournit un Update(dt) qui fait avancer l'animation et renvoie la frame courante.
 */
class AnimatedTile
{
public:
    AnimatedTile() = default;

    /// Ajoute une frame (tile + durée en secondes)
    void AddFrame(const Tile& tile, float durationSeconds);

    /// Vide toutes les frames
    void Clear();

    /// Met à jour l'animation (dt en secondes)
    void Update(float dtSeconds);

    /// Retourne la tile correspondant à la frame courante
    Tile GetCurrentTile() const;

    /// Réinitialise l'animation à la première frame
    void Reset();

    /// Indique si l'animation contient au moins une frame
    bool IsValid() const;

private:
    std::vector<Tile> m_frames;
    std::vector<float> m_durations;
    size_t m_current = 0;
    float m_elapsed = 0.0f;
};

} // namespace Editor::Map

#endif // _EDITOR_ANIMATEDTILE_HPP__
