#include "Renderer/Camera.hpp"

namespace Renderer
{

    Camera::Camera()
    {
        // Vue centrée en (0,0) avec une taille par défaut 800x600
        m_view.setCenter({0.f, 0.f});
        m_view.setSize({800.f, 600.f});
    }

    void Camera::setPosition(float x, float y)
    {
        m_view.setCenter({x, y});
    }

    void Camera::move(float dx, float dy)
    {
        m_view.move({dx, dy});
    }

    void Camera::zoom(float factor)
    {
        m_view.zoom(factor);
    }

    sf::View& Camera::getView()
    {
        return m_view;
    }

} // namespace Renderer
