#include "Editor/EditorUI.hpp"

#include <imgui-SFML.h>
#include <portable-file-dialogs.h>

namespace Editor {

EditorUI::EditorUI()
    //: m_docking(std::make_unique<UI::WindowDocking>()), 
    //m_tilePalette(std::make_unique<UI::TilePalette>()),
    //m_layerPanel(std::make_unique<UI::LayerPanel>()),
    //m_mapPanel(std::make_unique<UI::MapPanel>()),
    //m_npcPanel(std::make_unique<UI::NPCPanel>()),
    //m_shaderPanel(std::make_unique<UI::ShaderPanel>()),
    //m_propertyPanel(std::make_unique<UI::PropertyPanel>())
{
}

EditorUI::~EditorUI()
{
}

void EditorUI::Initialize(sf::RenderWindow& window, Project::ProjectManager& project)
{
    m_window = &window;
    m_project = &project;
    m_initialized = true;
}

void EditorUI::Shutdown()
{
    // Libération simple : unique_ptr s’occupe de tout
    m_initialized = false;
}

void EditorUI::ProcessEvent(const sf::Event& event)
{
    // Ici on pourrait transmettre des événements aux panels si nécessaire
}

void EditorUI::Update(float dt)
{
    if (!m_initialized) return;

    //if (m_tilePalette)   m_tilePalette->Update(dt, *m_project);
    //if (m_layerPanel)    m_layerPanel->Update(dt, *m_project);
    //if (m_mapPanel)      m_mapPanel->Update(dt, *m_project);
    //if (m_npcPanel)      m_npcPanel->Update(dt, *m_project);
    //if (m_shaderPanel)   m_shaderPanel->Update(dt, *m_project);
    //if (m_propertyPanel) m_propertyPanel->Update(dt, *m_project);
}

void EditorUI::Render(sf::RenderWindow& window)
{
    if (!m_initialized) return;

    // Dockspace + menu
    drawDockspace();
    drawMainMenu();

    // Panels
    drawPanels();
}

void EditorUI::drawDockspace()
{
    //m_docking->BeginDockspace();
    // Rien d'autre ici : les panels sont dessinés ensuite
}

void EditorUI::drawMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Project", "Ctrl+Shift+N"))
            {
                m_project->CreateEmptyProject();
            }
            if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
            {
                OnOpenProject();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                OnSaveProject();
            }
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
            {
                OnSaveProjectAs();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "Ctrl+Q"))
            {
                m_window->close();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Tile Palette"))    {}
            if (ImGui::MenuItem("Layers"))          {}
            if (ImGui::MenuItem("Map Editor"))      {}
            if (ImGui::MenuItem("NPCs"))            {}
            if (ImGui::MenuItem("Shaders"))         {}
            if (ImGui::MenuItem("Properties"))      {}

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void EditorUI::drawPanels()
{
    //if (m_tilePalette)   m_tilePalette->Draw(*m_project);
    //if (m_layerPanel)    m_layerPanel->Draw(*m_project);
    //if (m_mapPanel)      m_mapPanel->Draw(*m_project);
    //if (m_npcPanel)      m_npcPanel->Draw(*m_project);
    //if (m_shaderPanel)   m_shaderPanel->Draw(*m_project);
    //if (m_propertyPanel) m_propertyPanel->Draw(*m_project);

    //m_docking->EndDockspace();
}

//
// --- GESTION DES PROJETS ---
//

void EditorUI::OnOpenProject()
{
    pfd::open_file dialog("Open Project", ".", { "Project JSON", "*.json" });
    auto result = dialog.result();

    if (result.empty()) return;

    m_project->LoadProject(result[0]);
}

void EditorUI::OnSaveProject()
{
    if (!m_project->HasProjectPath())
    {
        OnSaveProjectAs();
        return;
    }

    m_project->SaveProject(m_project->GetProjectPath());
}

void EditorUI::OnSaveProjectAs()
{
    pfd::save_file dialog("Save Project As", ".", { "Project JSON", "*.json" });
    auto path = dialog.result();

    if (path.empty()) return;

    m_project->SaveProject(path);
}

} // namespace Editor
