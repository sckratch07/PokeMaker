#include "Editor/Panel/PanelManager.hpp"
#include "Editor/Panel/Panels.hpp"
#include <imgui.h>
#include <iostream>

namespace Editor
{
    void PanelManager::update()
    {
        docking();
        m_mapMenu->update(m_projectManager);
    }

    void PanelManager::handleEvents(const std::optional<sf::Event>& event)
    {
        PanelTab::shortcutProject(event, m_projectManager);
    }

    void PanelManager::docking()
    {
        ImGui::SetNextWindowSize(ImGui::GetCursorScreenPos());
        ImGui::SetNextWindowPos(ImGui::GetCursorStartPos());
        if (ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_DockNodeHost |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
        {
            ImGui::DockSpace(ImGui::GetID("DockSpace"), { 0,0 }, ImGuiDockNodeFlags_PassthruCentralNode);
            if (ImGui::BeginMainMenuBar())
            {
                PanelTab::projectTab(m_projectManager);
                PanelTab::helpTab();
            }
            ImGui::EndMainMenuBar();
        }
        ImGui::End();
    }
}