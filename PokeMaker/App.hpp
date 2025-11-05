#pragma once
#include "EditorState.hpp"

class App {
public:
    App();
    ~App();

    // Démarre la boucle principale
    void Run();
    // Gère la file d'événements SFML
    void ProcessEvents();
    // Mise à jour de la logique
    void Update(float dt);
    // Rendu
    void Render();

private:
    sf::RenderWindow window;
    sf::Time deltaTime;
    EditorState editorState;
    bool isRunning;
};
