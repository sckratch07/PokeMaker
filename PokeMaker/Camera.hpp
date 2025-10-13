#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& center, const sf::Vector2f& size);

    void HandleInput(const sf::Event& event);

    void Move(const sf::Vector2f& offset);
    void Zoom(float factor);
    void Update(float dt);
    void Apply(sf::RenderWindow& window);

    sf::View& GetView();
    sf::Vector2f GetCenter() const;
    float GetZoomLevel() const;

private:
    sf::View m_view;
    float m_moveSpeed;      // vitesse de déplacement caméra
    float m_zoomLevel;      // niveau de zoom actuel
};
