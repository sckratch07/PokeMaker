#ifndef _EDITOR_EDITORAPPLICATION_HPP__
#define _EDITOR_EDITORAPPLICATION_HPP__

/**
 * @file EditorApplication.hpp
 * @brief Classe principale de l'éditeur : boucle, fenêtre et intégration UI.
 *
 * Fournit l'initialisation SFML + ImGui-SFML, la boucle principale et les appels
 * vers EditorUI et autres modules d'édition.
 */

 
#include "Editor/EditorUI.hpp"
#include "Editor/EditorTool.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include <string>


namespace Editor {

/**
 * @class EditorApplication
 * @brief Point d'entrée et boucle principale de l'éditeur.
 */
class EditorApplication
{
public:
    /**
     * @brief Constructeur.
     * @param title Titre de la fenêtre.
     * @param width Largeur de la fenêtre.
     * @param height Hauteur de la fenêtre.
     */
    EditorApplication(const std::string& title = "PokeMaker - Editor", unsigned int width = 1280, unsigned int height = 720);

    /** @brief Destructeur. */
    ~EditorApplication();

    /** @brief Démarre l'application (boucle principale). */
    void run();

    /** @brief Demande l'arrêt de l'application. */
    void quit();

    /** @brief Accesseur vers la fenêtre SFML. */
    sf::RenderWindow& window();

    /** @brief Change l'outil utiliser */
    void requestToolChange(EditorToolType type);

private:
    void processEvents();
    void update(float dt);
    void render();

    void handleShortcuts(sf::Event& event);
    bool confirmSaveBeforeQuit();

private:
    std::unique_ptr<sf::RenderWindow> m_window;
    bool m_running;
    unsigned int m_width;
    unsigned int m_height;
    std::string m_title;

    EditorUI m_ui;

    // Outil actif
    std::unique_ptr<EditorTool> m_activeTool;
    EditorToolType m_pendingTool;

    // Autosave
    std::chrono::steady_clock::time_point m_lastAutoSave;
    float m_autoSaveIntervalSeconds;

    // state close confirmation
    bool m_closingRequested;
};

} // namespace Editor

#endif
