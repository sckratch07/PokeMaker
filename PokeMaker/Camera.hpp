#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    void HandleEvent(std::optional<sf::Event>& event);      // Gestion de l’input clavier/souris
    void Move(float dt);                                    // Déplacement relatif
    void Zoom(float factor);                                // Zoom relatif
    void Apply(sf::RenderWindow& window);                   // Appliquer la vue sur la fenêtre
    sf::Vector2f GetCenter() const;                         // Centre de la vue

    // Accesseurs / mutateurs
    const sf::View& GetView() const { return view; }
    void SetMoveSpeed(float speed) { moveSpeed = speed; }
    void SetZoomLevel(float zoom) { zoomLevel = zoom; }

private:
    sf::View view;
    float moveSpeed;
    float zoomLevel;
};
