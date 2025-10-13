#pragma once
#include <SFML/Graphics.hpp>
#include "EditorState.hpp"

class Application {
public:
    Application();
    ~Application();

    void Run();

private:
    void ProcessEvents();
    void Update(float dt);
    void Render();

private:
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;
    bool m_isRunning;

    EditorState m_editorState;
};
