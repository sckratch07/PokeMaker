#include "Editor/Panel/PanelManager.hpp"
#include "Editor/Panel/Panels.hpp"
#include <imgui.h>
#include <iostream>

namespace Editor
{
    void PanelManager::update()
    {
        beginDocking();

        m_mapMenu->update(m_projectManager);
        
        endDocking();
    }

    void PanelManager::handleEvents(const std::optional<sf::Event>& event)
    {
        PanelTab::shortcutProject(event, m_projectManager);
    }

    void PanelManager::beginDocking()
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        if (ImGui::Begin("Window", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus
            | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground))
        {
            ImGui::DockSpace(ImGui::GetID("DockSpace"), { 0,0 }, ImGuiDockNodeFlags_PassthruCentralNode);
            if (ImGui::BeginMainMenuBar())
            {
                PanelTab::projectTab(m_projectManager);
                PanelTab::helpTab();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void PanelManager::endDocking()
    {
        ImGui::End();
    }
}