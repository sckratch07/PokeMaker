#ifndef _RENDERER_CAMERA2D_HPP__
#define _RENDERER_CAMERA2D_HPP__

/**
 * @file Camera2D.hpp
 * @brief Camera 2D utilitaire pour SFML (panning, zoom, clamp, snapping, follow).
 *
 * Protection d'en-tête : _RENDERER_CAMERA2D_HPP__
 */

#include <SFML/Graphics.hpp>
#include <SFML/System/Angle.hpp>
#include <functional>

namespace Renderer {

/**
 * @class Camera2D
 * @brief Caméra 2D pour naviguer une scène tile-based.
 *
 * Usage :
 *  - set viewport size via SetViewportSize(w,h)
 *  - appeler Update(dt) chaque frame pour smoothing / suivre la cible
 *  - récupérer la sf::View via GetView() pour le rendu
 */
class Camera2D
{
public:
    Camera2D();

    /// Définit la taille de la vue (en pixels)
    void SetViewportSize(float width, float height);

    /// Retourne la view (const)
    const sf::View& GetView() const;

    /// Met à jour la caméra (lissage, suivi, limites), dt en secondes
    void Update(float dt);

    // Position / movement
    void SetCenter(const sf::Vector2f& center);
    sf::Vector2f GetCenter() const;
    void Move(const sf::Vector2f& delta);

    // Zoom
    void SetZoom(float zoom);          ///< zoom = 1.0 = 100%
    float GetZoom() const;
    void ZoomBy(float factor);         ///< multiplie le zoom par factor
    void SetZoomLimits(float minZoom, float maxZoom);

    // Rotation
    void SetRotation(float degrees);
    float GetRotation() const;

    // Smoothing
    void SetSmoothing(bool enabled);
    void SetSmoothSpeed(float speed);  ///< larger speed -> faster follow (seconds^-1)

    // Bounds (clamp)
    void SetBounds(const sf::FloatRect& bounds);
    void DisableBounds();
    bool HasBounds() const;

    // Grid snapping
    void SetGridSnap(bool enabled);
    void SetGridSize(float gridSize);  ///< one value (square grid)
    sf::Vector2f SnapToGrid(const sf::Vector2f& worldPos) const;

    // Follow target: provide a function returning world position to follow
    void SetFollowTarget(std::function<sf::Vector2f()> targetCallback);
    void ClearFollowTarget();

    // Axis locks
    void SetLockX(bool lock);
    void SetLockY(bool lock);

    // Helper conversions
    sf::Vector2f ScreenToWorld(const sf::Vector2f& screenPos, const sf::RenderTarget& target) const;
    sf::Vector2f WorldToScreen(const sf::Vector2f& worldPos, const sf::RenderTarget& target) const;

private:
    sf::View m_view;
    float m_zoom = 1.0f;
    float m_minZoom = 0.25f;
    float m_maxZoom = 4.0f;
    float m_rotation = 0.0f;

    bool m_smoothing = true;
    float m_smoothSpeed = 10.0f; // higher = faster

    bool m_hasBounds = false;
    sf::FloatRect m_bounds;

    bool m_gridSnap = false;
    float m_gridSize = 16.0f;

    bool m_lockX = false;
    bool m_lockY = false;

    std::function<sf::Vector2f()> m_followCallback = nullptr;

    // Internal: current center target for smoothing
    sf::Vector2f m_targetCenter{0.f, 0.f};

    // Internal helpers
    sf::Vector2f ApplyBounds(const sf::Vector2f& center) const;
    sf::Vector2f ApplyLocks(const sf::Vector2f& center) const;
};

} // namespace Renderer

#endif // _RENDERER_CAMERA2D_HPP__
