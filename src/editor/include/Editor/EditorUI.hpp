#ifndef _EDITOR_EDITORUI_HPP__
#define _EDITOR_EDITORUI_HPP__

/**
 * @file EditorUI.hpp
 * @brief Gestion complète de l'interface ImGui de l'éditeur.
 *
 * Fournit un dockspace, des panneaux, des barres de menus,
 * la fonction de rendu des panneaux et l'intégration SFML.
 */

#include <SFML/Graphics.hpp>
#include <imgui.h>

#include "Editor/Project/ProjectManager.hpp"

// Panels
#include "Editor/UI/TilePalette.hpp"
#include "Editor/UI/LayerPanel.hpp"
#include "Editor/UI/MapPanel.hpp"
#include "Editor/UI/NPCPanel.hpp"
#include "Editor/UI/ShaderPanel.hpp"
#include "Editor/UI/PropertyPanel.hpp"
#include "Editor/UI/WindowDocking.hpp"

namespace Editor {

/**
 * @class EditorUI
 * @brief Gère le docking ImGui, les fenêtres et les panneaux de l'éditeur.
 */
class EditorUI
{
public:
    EditorUI();
    ~EditorUI();

    /// Initialise les panels et le système UI
    void Initialize(sf::RenderWindow& window, Project::ProjectManager& project);

    /// Processus de shutdown
    void Shutdown();

    /// Gestion des événements SFML (clic, souris, clavier…)
    void ProcessEvent(const sf::Event& event);

    /// Mise à jour logique des panels
    void Update(float dt);

    /// Rendu des panneaux et de l'espace de travail
    void Render(sf::RenderWindow& window);

    // Opérations projet
    void OnOpenProject();
    void OnSaveProject();
    void OnSaveProjectAs();

private:
    // Barre de menu supérieure
    void drawMainMenu();

    // Dessine le dockspace principal
    void drawDockspace();

    // Dessine tous les panels
    void drawPanels();

private:
    bool m_initialized{false};

    // Pointeurs vers la fenêtre SFML et le manager de projet
    sf::RenderWindow* m_window{nullptr};
    Project::ProjectManager* m_project{nullptr};

    // Panels ImGui
    //std::unique_ptr<UI::WindowDocking> m_docking;
    //std::unique_ptr<UI::TilePalette> m_tilePalette;
    //std::unique_ptr<UI::LayerPanel> m_layerPanel;
    //std::unique_ptr<UI::MapPanel> m_mapPanel;
    //std::unique_ptr<UI::NPCPanel> m_npcPanel;
    //std::unique_ptr<UI::ShaderPanel> m_shaderPanel;
    //std::unique_ptr<UI::PropertyPanel> m_propertyPanel;
};

} // namespace Editor

#endif // _EDITOR_EDITORUI_HPP__
