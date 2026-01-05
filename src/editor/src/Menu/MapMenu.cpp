#include "Editor/Panel/MapMenu.hpp"
#include <imgui.h>

namespace Editor::PanelMenu
{
    void MapMenu::handleEvents(const std::optional<sf::Event>& event)
    {
        
    }

    void MapMenu::update(std::shared_ptr<Core::ProjectManager>& projectManager)
    {
        mapSelector(projectManager);
    }

    void MapMenu::mapSelector(std::shared_ptr<Core::ProjectManager>& projectManager)
    {
        if (ImGui::Begin("Map Selector"))
        {
            auto maps = projectManager->getMaps();
            for (int i = 0; i < maps.size(); i++)
            {
                if (ImGui::Selectable(maps[i].m_name.c_str(), (&maps[i] == m_currentMap)))
                    m_currentMap = &maps[i];
            }

            ImGui::Separator();

            ImGui::Text("Map name : ");
            ImGui::InputText("##MapName", m_bufferMapName, 50, ImGuiInputTextFlags_CharsNoBlank);
            ImGui::Text("Map size : ");
            ImGui::InputInt2("##MapSize", m_bufferMapSize, ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank);
            ImGui::Text("Tile size : ");
            ImGui::InputInt2("##TileSize", m_bufferTileSize, ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank);

            if (ImGui::Button("Create Map"))
                m_currentMap = projectManager->createNewMap(m_bufferMapName, m_bufferMapSize, m_bufferTileSize);
            ImGui::SameLine();
            if (ImGui::Button("Delete Map"))
            { 
                projectManager->deleteMap(m_currentMap);
                if (maps.empty()) m_currentMap = nullptr;
                else m_currentMap = &maps[0];
            }
        }
        ImGui::End();
    }

    void MapMenu::mapManage()
    {

    }

    void MapMenu::tilesetSelector()
    {

    }

    void MapMenu::tilePropriety()
    {

    }
}