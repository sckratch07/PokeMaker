#include "Camera.hpp"
#include <SFML/Window.hpp>

Camera::Camera(const sf::Vector2f& center, const sf::Vector2f& size) : m_moveSpeed(500.f), m_zoomLevel(1.f)
{
    this->m_view.setSize(size);
    this->m_view.setCenter(center);
}

void Camera::HandleInput(const sf::Event& event)
{
    if (event.is<sf::Event::MouseWheelScrolled>())
    {
        if (event.getIf<sf::Event::MouseWheelScrolled>()->delta > 0)
            this->Zoom(0.9f);   // zoom avant
        else
            this->Zoom(1.1f);   // zoom arrière
    }
}

void Camera::Move(const sf::Vector2f& offset)
{
    m_view.move(offset);
}

void Camera::Zoom(float factor)
{
    this->m_view.zoom(factor);
    this->m_zoomLevel *= factor;
}

void Camera::Update(float dt) {
    // Déplacement au clavier
    sf::Vector2f moveDelta(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) moveDelta.y = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) moveDelta.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) moveDelta.x = -1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) moveDelta.x = 1;

    this->m_view.move(moveDelta);
}

void Camera::Apply(sf::RenderWindow& window)
{
    window.setView(m_view);
}

sf::View& Camera::GetView()
{
    return m_view;
}

sf::Vector2f Camera::GetCenter() const
{
    return m_view.getCenter();
}

float Camera::GetZoomLevel() const
{
    return m_zoomLevel;
}
