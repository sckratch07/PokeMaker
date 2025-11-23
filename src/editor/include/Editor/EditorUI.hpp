#ifndef _EDITOR_EDITORUI_HPP__
#define _EDITOR_EDITORUI_HPP__

/**
 * @file EditorUI.hpp
 * @brief Interface utilisateur de l'éditeur basée sur ImGui.
 *
 * Fournit un panneau principal, une barre d'outils et l'intégration des sous-outils
 * (TilePalette, LayerManager, NPCEditor, etc.).
 */

#include "Editor/ProjectManager.hpp"
#include <memory>
#include <string>

namespace Editor {

class TilePalette;
class LayerManager;
class NPCEditor;

/**
 * @class EditorUI
 * @brief Gère l'interface ImGui de l'éditeur.
 */
class EditorUI
{
public:
    EditorUI();
    ~EditorUI();

    /** @brief Dessine l'UI (doit être appelé après ImGui::SFML::Update). */
    void render();

    /** 
     * @brief Renvoie le type de l'outil actuellement selectionné.
     * @return Valeur de l'enum EditorToolType
     */
    EditorToolType selectedTool() const;

    /**
     * @brief Retourne le type d'outil actuellement sélectionné (défini par les boutons).
     * L'application lira cette valeur pour instancier l'outil.
     */
    // Déclarée ailleurs dans l'implémentation ; on laisse l'interface minimale publique.
    // EditorToolType selectedTool() const;

    /** @brief Accès au gestionnaire de projet (pour l'application qui veut y accéder) */
    ProjectManager& projectManager();
private:
    void drawMainMenu();
    void drawToolBar();
    void drawDockspace();

    // UI WFC & autres panneaux
    std::unique_ptr<TilePalette> m_tilePalette;
    std::unique_ptr<LayerManager> m_layerManager;
    std::unique_ptr<NPCEditor> m_npcEditor;

    // Gestion de projet
    ProjectManager m_projectManager;

    // États UI pour les popups / dialogues
    bool m_showNewProjectPopup;
    bool m_showOpenProjectPopup;
    bool m_showSaveAsPopup;

    // Buffers pour saisie utilisateur
    char m_newProjectName[128];
    char m_openProjectPath[512];
    char m_saveAsPath[512];
    int m_width = 32;
    int m_height = 18;
    int m_seedValue = 0;
    int m_neighborToAdd = 0;
    int m_newRuleId = 0;
    bool m_useSeed = false;
    float m_newRuleWeight = 1.0f;
    std::vector<TileRule> m_rules;
    std::vector<int> m_generatedMap;

    // Tools
    EditorToolType m_currentTool = EditorToolType::Selection;
};

} // namespace Editor

#endif
