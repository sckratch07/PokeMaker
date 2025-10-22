#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera();

    void HandleEvent(std::optional<sf::Event>& event);      // Gestion de l’input clavier/souris
    void Move(float dt);                                    // Déplacement relatif
    void Zoom(float factor);                                // Zoom relatif
    void Apply(sf::RenderWindow& window);                   // Appliquer la vue sur la fenêtre

    // Accesseurs / mutateurs
    const sf::View& GetView() const { return view; }

private:
    sf::View view;
    float moveSpeed;
    float zoomLevel;
};
