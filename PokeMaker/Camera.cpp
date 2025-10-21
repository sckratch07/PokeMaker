#include "Camera.hpp"

Camera::Camera() : moveSpeed(300.f), zoomLevel(1.f)
{
    view = sf::View(sf::FloatRect({ -640.f, -360.f }, { 1280.f, 720.f })); // vue par défaut
}

Camera::~Camera()
{
}

void Camera::HandleEvent(std::optional<sf::Event>& event)
{
    // Zoom avec molette de souris
    if (event->is<sf::Event::MouseWheelScrolled>())
    {
        float deltaMouse = event->getIf<sf::Event::MouseWheelScrolled>()->delta;
        if (deltaMouse > 0)
            Zoom(0.9f);
        else if (deltaMouse < 0)
            Zoom(1.1f);
    }
}

void Camera::Move(float dt)
{
    // Déplacement avec flèches
    sf::Vector2f offset(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) offset.y = -1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) offset.y = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) offset.x = -1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) offset.x = 1;

    if (offset != sf::Vector2f(0.f, 0.f))
    {
        offset = offset.normalized() * (moveSpeed * dt);
        view.move(offset);
    }
}

void Camera::Zoom(float factor)
{
    zoomLevel *= factor;
    view.zoom(factor);
}

void Camera::Apply(sf::RenderWindow& window)
{
    window.setView(view);
}

sf::Vector2f Camera::GetCenter() const
{
    return view.getCenter();
}
