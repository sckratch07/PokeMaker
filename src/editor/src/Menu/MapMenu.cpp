#include "Editor/Panel/MapMenu.hpp"
#include <imgui.h>
#include <iostream>

namespace Editor::PanelMenu
{
    void MapMenu::handleEvents(const std::optional<sf::Event>& event)
    {
        
    }

    void MapMenu::update(std::shared_ptr<Core::ProjectManager>& projectManager)
    {
        mapSelector(projectManager);
        mapManage();
        tilesetSelector();
        tilePropriety();
    }

    void MapMenu::mapSelector(std::shared_ptr<Core::ProjectManager>& projectManager)
    {
        if (ImGui::Begin("Map Selector", nullptr, ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_DockNodeHost))
        {
            auto& maps = projectManager->getMaps();
            if (ImGui::BeginCombo("##MapSelectorCombo", m_currentMap != nullptr ? m_currentMap->m_name.c_str() : "No map..."))
            {
                for (int i = 0; i < maps.size(); i++)
                {
                    if (ImGui::Selectable(maps[i].m_name.c_str(), (&(maps[i]) == m_currentMap)))
                    {
                        m_currentMap = &maps[i];
                    }
                }
                ImGui::EndCombo();
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
                projectManager->deleteMap(m_currentMap, m_entityManager);
                if (maps.empty()) m_currentMap = nullptr;
                else m_currentMap = &maps[0];
            }
        }
        ImGui::End();
    }

    void MapMenu::mapManage()
    {
        if (m_currentMap == nullptr) return;
        if (ImGui::Begin("Map Manage", nullptr, ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_DockNodeHost))
        {
            ImGui::TextWrapped("Name : %s", m_currentMap->m_name.c_str());
            ImGui::SeparatorText("Dimension");
            ImGui::TextWrapped("Size : %d / %d (%d tiles per layer)", m_currentMap->m_width, m_currentMap->m_height, m_currentMap->m_width * m_currentMap->m_height);
            ImGui::TextWrapped("Tile : %d / %d", m_currentMap->m_tileWidth, m_currentMap->m_tileHeight);
            ImGui::SeparatorText("Data");
            ImGui::TextWrapped("%d Layer", m_currentMap->m_layers.size());
            ImGui::TextWrapped("%d Entity", m_currentMap->m_entities.size());                                                              
        }
        ImGui::End();
    }

    void MapMenu::tilesetSelector()
    {

    }

    void MapMenu::tilePropriety()
    {

    }
}