#ifndef _EDITOR_EDITORAPP_HPP__
#define _EDITOR_EDITORAPP_HPP__

/**
 * @file EditorApp.hpp
 * @brief Entrée principale et boucle de l'éditeur.
 *
 * Fournit la classe Editor::EditorApp qui gère :
 *  - l'initialisation SFML + ImGui-SFML
 *  - la boucle principale (événements, update, rendu)
 *  - le dispatch d'événements vers l'UI de l'éditeur
 *  - quelques raccourcis clavier globaux (ouvrir/sauver projet, quitter)
 *
 * Protection d'entête conforme : _EDITOR_EDITORAPP_HPP__
 */

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Editor/EditorUI.hpp"          // Interface UI de l'éditeur (panel dock, etc.)
#include "Editor/Project/ProjectManager.hpp"

namespace Editor {

/**
 * @class EditorApp
 * @brief Application principale de l'éditeur.
 *
 * Responsable de la fenêtre SFML, du contexte ImGui-SFML et de la boucle d'exécution.
 */
class EditorApp
{
public:
    /// Constructeur — initialise SFML, ImGui-SFML, les managers et l'UI.
    EditorApp(unsigned int width = 1280, unsigned int height = 720, const std::string& title = "PokeMaker Editor");

    /// Destructeur — nettoie proprement ImGui-SFML et libère les ressources.
    ~EditorApp();

    /// Démarre la boucle principale (bloquant tant que l'application tourne).
    void Run();

    /// Demande explicite de fermer l'application (peut être appelée par UI).
    void Quit();

private:
    // Helpers
    void initWindow(unsigned int width, unsigned int height, const std::string& title);
    void initImGui();
    void shutdownImGui();

    void processEvents();
    void update(float dt);
    void render();

    void handleShortcuts(const sf::Event& event);

private:
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;
    bool m_running{false};

    // Pointeurs vers systèmes internes de l'éditeur (implémentés ailleurs)
    std::unique_ptr<EditorUI> m_ui;                      ///< UI et panneaux ImGui
    std::unique_ptr<Project::ProjectManager> m_project;  ///< Gestion des projets

    // Configuration
    const sf::Color m_clearColor = {30, 30, 30, 255};
};

} // namespace Editor

#endif // _EDITOR_EDITORAPP_HPP__
