#ifndef _EDITOR_EDITORAPPLICATION_HPP__
#define _EDITOR_EDITORAPPLICATION_HPP__

/**
 * @file EditorApplication.hpp
 * @brief Application principale de l'éditeur (initialisation, boucle, shutdown).
 *
 * Protection d'en-tête respectée :
 * #ifndef _EDITOR_<FILE>_HPP__
 * #define _EDITOR_<FILE>_HPP__
 *
 * Utilise SFML, ImGui-SFML, EnTT et nlohmann::json pour piloter l'éditeur.
 */

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h> // selon installation ; si include différent -> adapter
#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

#include "Editor/ProjectManager.hpp"
#include "Editor/ViewController.hpp"
#include "Editor/GridRenderer.hpp"
#include "Editor/TilePalette.hpp"
#include "Editor/LayerManager.hpp"
#include "Editor/ResourceCache.hpp"

namespace Editor {

/**
 * @class EditorApplication
 * @brief Point d'entrée graphique et manager global de l'éditeur.
 *
 * Responsable :
 * - Création de la fenêtre SFML et intégration ImGui-SFML
 * - Cycle événement / update / rendu
 * - Conteneur des principaux sous-systèmes : ProjectManager, ViewController, etc.
 *
 * Utilisation typique :
 * EditorApplication app;
 * app.Init(...); 
 * app.Run();
 */
class EditorApplication
{
public:
    EditorApplication();
    ~EditorApplication();

    /// Initialise l'application (window size, title, ressources path)
    bool Init(const sf::Vector2u& windowSize = {1280, 720},
              const std::string& title = "PokeMaker - Editor",
              const std::string& resourcesPath = "../resources/");

    /// Lancer la boucle principale (bloquant)
    void Run();

    /// Forcer la fermeture (peut être appelé depuis UI)
    void Quit();

private:
    // boucle principale - séparées pour lisibilité / tests
    void ProcessEvents();
    void Update(sf::Time dt);
    void Render();

    // helpers
    void SetupImGuiStyle();
    void LoadDefaultResources();

private:
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock; ///< pour ImGui-SFML et updates
    bool m_running;

    // Entités / ECS
    entt::registry m_registry;

    // Sous-systèmes de l'éditeur (forwarded to implementations)
    std::unique_ptr<ProjectManager> m_projectManager;
    std::unique_ptr<ViewController> m_viewController;
    std::unique_ptr<GridRenderer> m_gridRenderer;
    std::unique_ptr<TilePalette> m_tilePalette;
    std::unique_ptr<LayerManager> m_layerManager;
    std::unique_ptr<ResourceCache> m_resourceCache;

    // chemin ressource global
    std::string m_resourcesPath;
};

} // namespace Editor

#endif // _EDITOR_EDITORAPPLICATION_HPP__
