#include "EditorUI.hpp"
#include "Application.hpp"
#include "tinyfiledialogs.h"

extern Application game;
int tileMapSize[2] = { 10, 10 };
int tileSize[2] = { 16, 16 };
std::string tileSetPath = "";


void EditorUI::drawProjectPanel()
{
    ProjectManager& projectManager = game.getProjectManager();
    if (!projectManager.projectLoaded())
        return;

    ProjectData& project = projectManager.getCurrentProject();
    const char* imageFilters[] = { "*.png", "*.jpeg" };
    const char* mapFilters[] = { "*.pokeMap" };

    if (ImGui::Begin("Project Panel", nullptr, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::Text("Project: %s", project.projectName.c_str());
        ImGui::Separator();

        ImGui::Text("Maps:");
        for (MapInfo& map : project.maps)
        {
            if (ImGui::Selectable(map.id.c_str()))
            {
                game.getSceneManager().loadMap(map.id);
            }
        }

        if (ImGui::Button("New Map"))
        {
            ImGui::OpenPopup("Create Map");
        }

        ImGui::Separator();

        ImGui::Text("Player:");
        ImGui::Text("Spawn: (%.1f, %.1f)", project.playerInfo.spawn.x, project.playerInfo.spawn.y);
        if (ImGui::Button("Edit Player"))
        {
            showEntityEditor = true;
        }

        ImGui::Separator();

        if (ImGui::Button("Save Project"))
        {
            projectManager.saveProject();
        }

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("Create Map", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
        {
            ImGui::SetItemDefaultFocus();
            ImGui::Text("Map Size :");
            ImGui::InputInt2("##newMapSize", tileMapSize, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsDecimal);

            ImGui::Text("Tile Size :");
            ImGui::InputInt2("##newTileSize", tileSize, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsDecimal);

            if (ImGui::Button("Tile Set"))
            {
                const char* path = tinyfd_openFileDialog("Create Project", "../project/", 1, imageFilters, "Image files (*.png, *.jpeg)", 0);
                if (path)
                {
                    tileSetPath = path;
                }
            }
            ImGui::SameLine();
            ImGui::Text(tileSetPath.c_str());
            
            if (ImGui::Button("Create"))
            {
                const char* path = tinyfd_saveFileDialog("CreateMap", "../project/", 1, mapFilters, "Image files (*.pokeMap)");
                if (path)
                {
                    TileMap newMap;
                    newMap.setMapSize(tileMapSize[0], tileMapSize[1]);
                    newMap.setTileSize(tileSize[0], tileSize[1]);
                    if (tileSetPath != "") newMap.setTileSetPath(tileSetPath);

                    int id = project.maps.size() - 1;
                    project.maps.push_back({ std::to_string(id + 1), path });

                    newMap.saveToFile(path);

                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
    ImGui::End();

    
}

void EditorUI::drawTileMapEditor()
{
	if (this->showTileMapEditor)
    {
        this->mapEditor.paintTile();
    }
}

void EditorUI::drawEntityEditor()
{

}
