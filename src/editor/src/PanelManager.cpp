#include "Editor/Panel/PanelManager.hpp"
#include "Editor/Panel/Panels.hpp"
#include <imgui.h>

namespace Editor
{
    void PanelManager::update()
    {
        docking();

        bool activeProject = m_projectManager->getProject() != nullptr;
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("New Project", "Ctrl + N"))
                {
                    
                }
                if (ImGui::MenuItem("Open Project", "Ctrl + O"))
                {
                    
                }
                if (activeProject)
                {
                    if (ImGui::MenuItem("Save Project", "Ctrl + S"))
                    {
                        m_projectManager->saveProject();
                    }
                    if (ImGui::MenuItem("Close Project", "Ctrl + K"))
                    {
                        m_projectManager->closeProject();
                    }
                }
                
            }
        }
        ImGui::EndMainMenuBar()
    }

    void PanelManager::handleEvents(const std::optional<sf::Event>& event)
    {

    }

    void PanelManager::docking()
    {
        if (ImGui::Begin("dockspace", nullptr, ImGuiWindowFlags_DockNodeHost | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration| ImGuiWindowFlags_NoResize))
        {
            ImGui::DockSpace(ImGui::GetID("DockSpace"), { 0,0 }, ImGuiDockNodeFlags_PassthruCentralNode);
        }
    }
}