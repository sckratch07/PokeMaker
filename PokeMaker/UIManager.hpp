#pragma once
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>
#include <string>
#include <vector>

#include "ProjectManager.hpp"
#include "Tileset.hpp"
#include "Layer.hpp"
#include "Tile.hpp"

class UIManager {
public:
    UIManager();

    void RenderMainMenu(ProjectManager& projectManager);
    void RenderTileSelector(Tileset& tileset);
    void RenderLayerPanel(std::vector<Layer>& layers);
    void RenderPropertiesPanel(Tile* selectedTile);
    void HandleMenuActions(ProjectManager& projectManager);

    // Accesseurs
    bool IsTileSelectorVisible() const { return showTileSelector; }
    bool IsLayersPanelVisible() const { return showLayersPanel; }
    bool IsPropertiesPanelVisible() const { return showPropertiesPanel; }

    int GetSelectedTileID() const { return selectedTileID; }
    int GetSelectedLayer() const { return selectedLayer; }

    const std::string& GetSelectedProjectPath() const { return selectedProjectPath; }

private:
    bool showTileSelector = true;
    bool showLayersPanel = true;
    bool showPropertiesPanel = true;

    int selectedTileID;
    int selectedLayer;
    std::string selectedProjectPath;

    bool createProjectPopupOpen = false;
    char newProjectPath[256];
};
