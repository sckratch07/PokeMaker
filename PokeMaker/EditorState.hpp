#pragma once
#include <SFML/Graphics.hpp>
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "UIManager.hpp"
#include "ProjectManager.hpp"
#include "MapEditor.hpp"
#include "Camera.hpp"

class EditorState {
public:
    EditorState();
    ~EditorState() = default;

    void Init();

    void HandleInput(const sf::Event& event);
    void Update(float dt);
    void Render(sf::RenderWindow& window);

private:
    // Sous-systèmes
    UIManager m_uiManager;
    ProjectManager m_projectManager;
    MapEditor m_mapEditor;
    Camera m_camera;

    // États internes
    bool m_showDemoWindow;     // Fenêtre ImGui de debug
    bool m_projectLoaded;      // Indique si un projet est chargé
};
