#include "Renderer/Camera2D.hpp"
#include <algorithm>
#include <cmath>

namespace Renderer {

Camera2D::Camera2D()
{
    m_view = sf::View(sf::FloatRect({0.f, 0.f}, {1280.f, 720.f}));
    m_zoom = 1.0f;
    m_targetCenter = m_view.getCenter();
}

void Camera2D::SetViewportSize(float width, float height)
{
    if (width <= 0.f || height <= 0.f) return;
    m_view.setSize({width, height});
    // keep zoom applied
    m_view.zoom(m_zoom);
}

const sf::View& Camera2D::GetView() const
{
    return m_view;
}

void Camera2D::Update(float dt)
{
    // Determine desired center: follow target if any, else current center
    sf::Vector2f desired = m_view.getCenter();
    if (m_followCallback) {
        desired = m_followCallback();
    } else {
        desired = m_targetCenter;
    }

    // Apply locks: locks freeze axis to current view center
    desired = ApplyLocks(desired);

    // Apply grid snap if enabled
    if (m_gridSnap) desired = SnapToGrid(desired);

    // Apply bounds clamp before smoothing for correctness
    if (m_hasBounds) desired = ApplyBounds(desired);

    if (m_smoothing && dt > 0.f) {
        // Exponential smoothing towards desired center
        // faster smoothing when m_smoothSpeed larger
        float alpha = 1.0f - std::exp(-m_smoothSpeed * dt);
        sf::Vector2f current = m_view.getCenter();
        sf::Vector2f next = current + (desired - current) * alpha;
        m_view.setCenter(next);
    } else {
        m_view.setCenter(desired);
    }

    // ensure rotation and zoom applied in view
    m_view.setRotation(sf::degrees(m_rotation));

    // update internal target center
    m_targetCenter = m_view.getCenter();
}

void Camera2D::SetCenter(const sf::Vector2f& center)
{
    m_targetCenter = center;
    m_view.setCenter(center);
}

sf::Vector2f Camera2D::GetCenter() const
{
    return m_view.getCenter();
}

void Camera2D::Move(const sf::Vector2f& delta)
{
    SetCenter(m_view.getCenter() + delta);
}

void Camera2D::SetZoom(float zoom)
{
    if (zoom <= 0.f) return;
    float clamped = std::clamp(zoom, m_minZoom, m_maxZoom);
    // adjust view size relatively to keep current center/dimensions visually consistent
    // compute ratio to apply to view
    float factor = clamped / m_zoom;
    m_view.zoom(factor);
    m_zoom = clamped;
}

float Camera2D::GetZoom() const { return m_zoom; }

void Camera2D::ZoomBy(float factor)
{
    if (factor <= 0.f) return;
    SetZoom(m_zoom * factor);
}

void Camera2D::SetZoomLimits(float minZoom, float maxZoom)
{
    if (minZoom <= 0.f) minZoom = 0.01f;
    if (maxZoom < minZoom) maxZoom = minZoom;
    m_minZoom = minZoom;
    m_maxZoom = maxZoom;
    // clamp current zoom
    SetZoom(m_zoom);
}

void Camera2D::SetRotation(float degrees)
{
    m_rotation = degrees;
    m_view.setRotation(sf::degrees(degrees));
}

float Camera2D::GetRotation() const { return m_rotation; }

void Camera2D::SetSmoothing(bool enabled) { m_smoothing = enabled; }
void Camera2D::SetSmoothSpeed(float speed) { m_smoothSpeed = std::max(0.0f, speed); }

void Camera2D::SetBounds(const sf::FloatRect& bounds)
{
    m_bounds = bounds;
    m_hasBounds = true;
    // ensure current center inside bounds
    SetCenter(ApplyBounds(m_view.getCenter()));
}

void Camera2D::DisableBounds()
{
    m_hasBounds = false;
}

bool Camera2D::HasBounds() const { return m_hasBounds; }

void Camera2D::SetGridSnap(bool enabled) { m_gridSnap = enabled; }
void Camera2D::SetGridSize(float gridSize) { m_gridSize = std::max(1.0f, gridSize); }

sf::Vector2f Camera2D::SnapToGrid(const sf::Vector2f& worldPos) const
{
    if (m_gridSize <= 0.f) return worldPos;
    float gx = std::floor(worldPos.x / m_gridSize + 0.5f) * m_gridSize;
    float gy = std::floor(worldPos.y / m_gridSize + 0.5f) * m_gridSize;
    return { gx, gy };
}

void Camera2D::SetFollowTarget(std::function<sf::Vector2f()> targetCallback)
{
    m_followCallback = targetCallback;
}

void Camera2D::ClearFollowTarget()
{
    m_followCallback = nullptr;
}

void Camera2D::SetLockX(bool lock) { m_lockX = lock; }
void Camera2D::SetLockY(bool lock) { m_lockY = lock; }

sf::Vector2f Camera2D::ScreenToWorld(const sf::Vector2f& screenPos, const sf::RenderTarget& target) const
{
    // sf::RenderTarget::mapPixelToCoords expects integer pixel coords, but we accept floats -> convert accordingly
    sf::Vector2i pixel(static_cast<int>(std::lround(screenPos.x)), static_cast<int>(std::lround(screenPos.y)));
    return target.mapPixelToCoords(pixel, m_view);
}

sf::Vector2f Camera2D::WorldToScreen(const sf::Vector2f& worldPos, const sf::RenderTarget& target) const
{
    sf::Vector2i coords = target.mapCoordsToPixel(worldPos, m_view);
    return sf::Vector2f(coords.x, coords.y);
}

sf::Vector2f Camera2D::ApplyBounds(const sf::Vector2f& center) const
{
    if (!m_hasBounds) return center;

    // view halfsize in world coordinates considering zoom and rotation (rotation effect is ignored for bounds simplicity)
    sf::Vector2f size = m_view.getSize();
    float halfW = size.x * 0.5f;
    float halfH = size.y * 0.5f;

    float minX = m_bounds.position.x + halfW;
    float maxX = m_bounds.position.x + m_bounds.size.x - halfW;
    float minY = m_bounds.position.y + halfH;
    float maxY = m_bounds.position.y + m_bounds.size.y - halfH;

    sf::Vector2f clamped = center;
    if (minX <= maxX) clamped.x = std::clamp(center.x, minX, maxX);
    if (minY <= maxY) clamped.y = std::clamp(center.y, minY, maxY);

    return clamped;
}

sf::Vector2f Camera2D::ApplyLocks(const sf::Vector2f& center) const
{
    sf::Vector2f result = center;
    if (m_lockX) result.x = m_targetCenter.x;
    if (m_lockY) result.y = m_targetCenter.y;
    return result;
}

} // namespace Renderer
