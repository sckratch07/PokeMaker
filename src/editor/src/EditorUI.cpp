#include "Editor/EditorUI.hpp"
#include "Editor/TilePalette.hpp"
#include "Editor/LayerManager.hpp"
#include "Editor/NPCEditor.hpp"
#include "Editor/WFCGenerator.hpp"
#include "Editor/Tools/SelectionTool.hpp"
#include "Editor/Tools/BrushTool.hpp"
#include "Editor/Tools/FillTool.hpp"


#include <imgui.h>

namespace Editor {

EditorUI::EditorUI()
    : m_tilePalette(std::make_unique<TilePalette>())
    , m_layerManager(std::make_unique<LayerManager>())
    , m_npcEditor(std::make_unique<NPCEditor>())
    , m_showNewProjectPopup(false)
    , m_showOpenProjectPopup(false)
    , m_showSaveAsPopup(false)
{
    std::memset(m_newProjectName, 0, sizeof(m_newProjectName));
    std::memset(m_openProjectPath, 0, sizeof(m_openProjectPath));
    std::memset(m_saveAsPath, 0, sizeof(m_saveAsPath));
}

EditorUI::~EditorUI() = default;

ProjectManager& EditorUI::projectManager()
{
    return m_projectManager;
}

void EditorUI::render()
{
    drawDockspace();
    drawToolBar();

    // Panneaux
    ImGui::Begin("Palette de tuiles");
    m_tilePalette->render();
    ImGui::End();

    ImGui::Begin("Calques");
    m_layerManager->render();
    ImGui::End();

    ImGui::Begin("NPC Editor");
    m_npcEditor->render();
    ImGui::End();

    if (ImGui::Begin("WFC Generator"))
    {
        // --- Paramètres généraux ---
        ImGui::InputInt("Largeur", &m_width);
        ImGui::InputInt("Hauteur", &m_height);
        ImGui::Checkbox("Utiliser une seed ?", &m_useSeed);
        if (m_useSeed)
        {
            ImGui::InputInt("Seed", &m_seedValue);
        }

        ImGui::Separator();

        // Ajouter une nouvelle règle
        ImGui::Text("Ajouter une règle :");
        ImGui::InputInt("ID tuile", &m_newRuleId);
        ImGui::InputFloat("Poids", &m_newRuleWeight);

        if (ImGui::Button("Ajouter règle"))
        {
            TileRule r;
            r.id = m_newRuleId;
            r.weight = m_newRuleWeight;
            r.neighbors["up"] = {};
            r.neighbors["down"] = {};
            r.neighbors["left"] = {};
            r.neighbors["right"] = {};
            this->m_rules.push_back(r);
        }

        // Affichage / édition des règles existantes
        ImGui::Separator();
        ImGui::Text("Règles existantes :");

        for (int i = 0; i < this->m_rules.size(); ++i)
        {
            ImGui::PushID(i);
            TileRule& r = m_rules[i];

            if (ImGui::TreeNode(("Tuile ID " + std::to_string(r.id)).c_str()))
            {
                ImGui::InputFloat("Poids", &r.weight);

                // Ajouter voisins
                auto drawNeighborEditor = [&](const char* dir)
                {
                    ImGui::Text("%s :", dir);
                    for (int& id : r.neighbors[dir])
                    {
                        ImGui::BulletText("%d", id);
                    }

                    ImGui::InputInt(("Ajouter voisin " + std::string(dir)).c_str(), &m_neighborToAdd);
                    if (ImGui::Button(("Ajouter##" + std::string(dir)).c_str()))
                    {
                        r.neighbors[dir].push_back(m_neighborToAdd);
                    }
                };

                drawNeighborEditor("up");
                drawNeighborEditor("down");
                drawNeighborEditor("left");
                drawNeighborEditor("right");

                if (ImGui::Button("Supprimer la règle"))
                {
                    m_rules.erase(m_rules.begin() + i);
                    ImGui::TreePop();
                    ImGui::PopID();
                    break;
                }

                ImGui::TreePop();
            }
            ImGui::PopID();
        }

        ImGui::Separator();


        if (ImGui::Button("Générer la map"))
        {
            WFCGenerator generator;

            if (m_useSeed)
                generator.setSeed(m_seedValue);
            else
                generator.setSeed(std::nullopt);

            for (auto& r : m_rules)
                generator.addRule(r);

            m_generatedMap = generator.generate(m_width, m_height);
        }

        ImGui::Separator();

        // Affichage résultat (debug)
        if (!m_generatedMap.empty())
        {
            ImGui::Text("Carte générée :");

            for (int y = 0; y < m_height; ++y)
            {
                std::string line;
                for (int x = 0; x < m_width; ++x)
                    line += std::to_string(m_generatedMap[y * m_width + x]) + " ";
                ImGui::Text("%s", line.c_str());
            }
        }
    }
    ImGui::End();

    // Popups pour projets (si demandés)
    if (m_showNewProjectPopup) {
        ImGui::OpenPopup("Nouveau projet");
        m_showNewProjectPopup = false;
    }
    if (m_showOpenProjectPopup) {
        ImGui::OpenPopup("Ouvrir un projet");
        m_showOpenProjectPopup = false;
    }
    if (m_showSaveAsPopup) {
        ImGui::OpenPopup("Sauvegarder sous...");
        m_showSaveAsPopup = false;
    }

    // Nouveau projet
    if (ImGui::BeginPopupModal("Nouveau projet", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Nom du projet :");
        ImGui::InputText("##newprojectname", m_newProjectName, sizeof(m_newProjectName));
        ImGui::Separator();
        if (ImGui::Button("Créer")) {
            std::string name(m_newProjectName);
            if (!name.empty()) {
                m_projectManager.createProject(name);
                // Reset champs
                std::memset(m_newProjectName, 0, sizeof(m_newProjectName));
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Annuler")) {
            std::memset(m_newProjectName, 0, sizeof(m_newProjectName));
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    // Ouvrir projet
    if (ImGui::BeginPopupModal("Ouvrir un projet", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Chemin du fichier projet (.json) :");
        ImGui::InputText("##openprojectpath", m_openProjectPath, sizeof(m_openProjectPath));
        ImGui::Separator();
        if (ImGui::Button("Ouvrir")) {
            std::string path(m_openProjectPath);
            if (!path.empty()) {
                bool ok = m_projectManager.loadProject(path);
                if (!ok) {
                    // Message d'erreur simple (on peut améliorer avec un popup d'erreur)
                    ImGui::OpenPopup("Erreur ouverture");
                } else {
                    std::memset(m_openProjectPath, 0, sizeof(m_openProjectPath));
                    ImGui::CloseCurrentPopup();
                }
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Annuler")) {
            std::memset(m_openProjectPath, 0, sizeof(m_openProjectPath));
            ImGui::CloseCurrentPopup();
        }

        // Popup d'erreur
        if (ImGui::BeginPopupModal("Erreur ouverture", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Impossible d'ouvrir le fichier de projet. Vérifiez le chemin et le format JSON.");
            if (ImGui::Button("OK")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::EndPopup();
    }

    // Sauvegarder sous...
    if (ImGui::BeginPopupModal("Sauvegarder sous...", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Chemin de sauvegarde (.json) :");
        ImGui::InputText("##saveaspath", m_saveAsPath, sizeof(m_saveAsPath));
        ImGui::Separator();
        if (ImGui::Button("Sauvegarder")) {
            std::string path(m_saveAsPath);
            if (!path.empty()) {
                bool ok = m_projectManager.saveProjectAs(path);
                if (!ok) {
                    ImGui::OpenPopup("Erreur sauvegarde");
                } else {
                    std::memset(m_saveAsPath, 0, sizeof(m_saveAsPath));
                    ImGui::CloseCurrentPopup();
                }
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Annuler")) {
            std::memset(m_saveAsPath, 0, sizeof(m_saveAsPath));
            ImGui::CloseCurrentPopup();
        }

        // Popup d'erreur
        if (ImGui::BeginPopupModal("Erreur sauvegarde", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Impossible de sauvegarder le projet. Vérifiez les permissions et le chemin.");
            if (ImGui::Button("OK")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::EndPopup();
    }

    // Affichage d'état projet courant en bas de l'UI (simple)
    ImGui::Begin("Project");
    if (m_projectManager.activeProject) {
        ImGui::Text("Projet : %s", m_projectManager.activeProject->name.c_str());
        if (!m_projectManager.currentFilePath.empty())
            ImGui::Text("Chemin : %s", m_projectManager.currentFilePath.c_str());
        else
            ImGui::Text("Chemin : (non sauvegardé)");
    } else {
        ImGui::Text("Aucun projet ouvert.");
    }
    ImGui::End();
}

EditorToolType EditorUI::selectedTool() const
{
    return m_currentTool;
}

void EditorUI::drawMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Fichier"))
        {
            if (ImGui::MenuItem("Nouveau", "Ctrl + N"))
                m_showNewProjectPopup = true;
            if (ImGui::MenuItem("Ouvrir", "Ctrl + O"))
                m_showOpenProjectPopup = true;
            if (ImGui::MenuItem("Sauvegarder", "Ctrl+S"))
            {
                // Si projet actif et chemin connu -> save, sinon open Save As popup
                if (m_projectManager.activeProject) {
                    if (m_projectManager.currentFilePath.empty()) {
                        m_showSaveAsPopup = true;
                    }
                    else {
                        bool ok = m_projectManager.saveProject();
                        if (!ok) {
                            // ouvrir Save As en cas d'échec (permissions, etc.)
                            m_showSaveAsPopup = true;
                        }
                    }
                }
            }
            if (ImGui::MenuItem("Sauvegarder sous..."))
                if (m_projectManager.activeProject)
                    m_showSaveAsPopup = true;
            if (ImGui::MenuItem("Quitter"))
            {
                // Request close via ImGui: on laisse EditorApplication gérer la fermeture.
                // On poste un événement simple : ouvrir un flag global pourrait être
                // utilisé, mais pour rester découplé, on peut fermer la fenêtre via
                // la fonction standard (non implémentée ici).
                // L'application principale doit vérifier le menu ou fournir un callback.
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Édition"))
        {
            ImGui::MenuItem("Annuler", "Ctrl+Z");
            ImGui::MenuItem("Rétablir", "Ctrl+Y");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void EditorUI::drawToolBar()
{
    ImGui::Begin("Outils", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    if (ImGui::Button("Sélection")) {
        m_currentTool = EditorToolType::Selection;
    }
    ImGui::SameLine();
    if (ImGui::Button("Pinceau")) {
        m_currentTool = EditorToolType::Brush;
    }
    ImGui::SameLine();
    if (ImGui::Button("Remplissage")) {
        m_currentTool = EditorToolType::Fill;
    }

    // Affichage de l’outil actif
    ImGui::Text("Outil actif : ");

    switch (m_currentTool)
    {
        case EditorToolType::Selection: ImGui::Text("Sélection"); break;
        case EditorToolType::Brush:     ImGui::Text("Pinceau"); break;
        case EditorToolType::Fill:      ImGui::Text("Remplissage"); break;
    }

    ImGui::End();
}


void EditorUI::drawDockspace()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize(viewport->Size);
    if (ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar))
    {
        ImGui::DockSpace(ImGui::GetID("DockSpace"), { 0,0 }, ImGuiDockNodeFlags_PassthruCentralNode);
        drawMainMenu();
    }
    ImGui::End();
}
}