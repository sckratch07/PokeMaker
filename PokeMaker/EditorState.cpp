#include "EditorState.hpp"
#include "tinyfiledialogs.h"
#include <iostream>
#include <fstream>

EditorState::EditorState() : activeProject(nullptr), createProjectPopupOpen(false), selectedLayer(0), selectedTileID(0), tileSize(32,32), nameLayer("\n") {}

void EditorState::Init()
{
    // Initialisation des gestionnaires internes
    projectManager = ProjectManager();
    mapEditor = MapEditor();
    camera = Camera();
}

void EditorState::HandleEvent(std::optional<sf::Event>& event)
{
    camera.HandleEvent(event);
}

void EditorState::Update(float dt, sf::RenderWindow& window)
{
    camera.Move(dt);
    mapEditor.Update(dt, window, selectedTileID, selectedLayer, camera);

    // Interface ImGui
    ImGui::SetNextWindowPos({ 0,0 });
    ImGui::SetNextWindowSize({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    if (ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_MenuBar))
    {
        ImGui::DockSpace(ImGui::GetID("DockSpace"), { 0,0 }, ImGuiDockNodeFlags_PassthruCentralNode);
        RenderMainMenu();
    }
    ImGui::End();

    // Si une map est chargée, afficher les widgets
    if (activeProject)
    {
        RenderLayerPanel();
        RenderTileSelector();
    }

    if (projectManager.IsNewProject())
    {
        activeProject = projectManager.GetCurrentProject();

        if (activeProject->GetMaps().size() == 0)
            mapEditor.NewMap("Default", { 10, 10 }, { 32, 32 }, projectManager);
        else
            mapEditor.SetActiveMap(activeProject->GetMap("Default"));

        projectManager.ProjectIsLoaded(false);
    }
}

void EditorState::Render(sf::RenderWindow& window)
{
    // Appliquer la vue de la caméra
    camera.Apply(window);

    // Rendu de la carte active
    mapEditor.Render(window);

    // Rendu final ImGui
    ImGui::SFML::Render(window);
}

void EditorState::RenderMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
            {
                createProjectPopupOpen = true;
            }
            if (ImGui::MenuItem("Open"))
            {
                const char* path = tinyfd_selectFolderDialog("Open projet...", "..");
                if (path)
                    projectManager.LoadProject(std::string(path) + "/" + std::filesystem::path(path).stem().string() + ".json");
            }
            if (ImGui::MenuItem("Save"))
            {
                std::filesystem::path path = projectManager.GetCurrentProject()->GetBasePath();
                projectManager.SaveProject(path.string() + "/" + path.stem().string() + ".json");
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Display"))
        {
            ImGui::MenuItem("Tile Selector", nullptr, &showTileSelector);
            ImGui::MenuItem("Layers Panel", nullptr, &showLayersPanel);
            ImGui::EndMenu();
        }

        if (createProjectPopupOpen)
        {
            ImGui::OpenPopup("Create new project");
            createProjectPopupOpen = false;
        }

        if (ImGui::BeginPopupModal("Create new project", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            if (ImGui::Button("Create"))
            {
                const char* pathChar = tinyfd_selectFolderDialog("Create projet...", "..");
                if (pathChar)
                {
                    std::string path = pathChar;
                    std::string name = std::filesystem::path(path).stem().string();

                    if (!std::filesystem::exists(path))
                        std::filesystem::create_directories(path);

                    if (!projectManager.CreateProject(name, path))
                        std::cerr << "[Error] Couldn't create new project..." << std::endl;

                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }
        ImGui::EndMainMenuBar();
    }
}

void EditorState::RenderTileSelector()
{
    if (!showTileSelector) return;

    std::vector<Tileset*>& tilesets = mapEditor.GetActiveMap()->GetTilesets();
    const char* filters[] = { "*.png", "*.jpeg", "*.jpg" };

    ImGui::Begin("Tile Selector", &showTileSelector);

    if (tilesets.size() != 0)
    {
        if (tilesets.size() > 1)
        {
            if (ImGui::BeginChild("Tileset List Selector", ImVec2(0, 0), ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY,
                ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground |
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove))
            {
                for (int i = 0; i < tilesets.size(); i++)
                {
                    ImGui::PushID(i);

                    if (ImGui::Selectable(std::filesystem::path(tilesets[i]->GetPath()).filename().string().c_str(), mapEditor.GetActiveTilesets() == i))
                    {
                        mapEditor.GetActiveTilesets() = i;
                    }

                    ImGui::PopID();
                }
            }
            ImGui::EndChild();
            ImGui::Separator();
        }

        Tileset* currentTileset = tilesets[mapEditor.GetActiveTilesets()];

        const sf::Texture& tex = currentTileset->GetTexture();
        const sf::Vector2i& tileSize = currentTileset->GetTileSize();

        sf::Vector2f tileButtonSize(tileSize);
        int columns = tex.getSize().x / tileSize.x;
        int rows = tex.getSize().y / tileSize.y;


        // Utiliser ImGui::ImageButton pour chaque tile
        sf::Sprite sprt(tex);
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < columns; ++x)
            {
                int id = y * columns + x;

                sf::IntRect rect = currentTileset->GetTileTextureRect(id);
                sprt.setTextureRect(rect);
                
                if (ImGui::ImageButton(std::string("##Tile" + std::to_string(id)).c_str(), sprt, tileButtonSize))
                {
                    selectedTileID = id;
                }

                if (x < columns - 1)
                    ImGui::SameLine(0.f, 0.15f);
            }
        }
        ImGui::Separator();
    }
    if (ImGui::Button("Create"))
    {
        ImGui::OpenPopup("New Tileset");
    }
    if (tilesets.size() > 1)
    {
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            mapEditor.DeleteTileset(mapEditor.GetActiveTilesets());
        }
    }

    if (ImGui::BeginPopupModal("New Tileset"))
    {
        ImGui::Text("Tile Size : ");
        ImGui::InputInt2("##tileSize", tileSize, ImGuiInputTextFlags_AutoSelectAll);

        if (ImGui::Button("Create"))
        {
            const char* path = tinyfd_openFileDialog("Open tileset...", "..", 0, filters, "Image (*.png, *.jpeg, *.jpg)", 0);
            if (path)
            {
                std::string strPath(path);
                mapEditor.LoadTileset(strPath, {tileSize[0], tileSize[1]});
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void EditorState::RenderLayerPanel()
{
    if (!showLayersPanel) return;

    if (ImGui::Begin("Layers", &showLayersPanel))
    {
        std::vector<Layer>& layers = mapEditor.GetActiveMap()->GetLayers();
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        for (size_t i = 0; i < layers.size(); ++i)
        {
            Layer& layer = layers[i];
            std::string label = "##" + std::to_string(i);

            bool visible = layer.IsVisible();
            if (ImGui::Checkbox(label.c_str(), &visible))
            {
                layer.SetVisible(visible);
            }
            ImGui::SameLine();
            ImVec2 startCursor(ImGui::GetCursorScreenPos());
            ImGui::Text(layer.GetName().c_str());

            if (layer.GetID() == selectedLayer)
            {
                ImVec2 textSize = ImGui::CalcTextSize(layer.GetName().c_str());
                ImVec2 endCursor(startCursor.x + textSize.x, startCursor.y + textSize.y);

                startCursor.x -= 2.0f;
                startCursor.y += 2.0f;
                endCursor.x += 6.0f;
                endCursor.y += 6.0f;

                drawList->AddRect(startCursor, endCursor, IM_COL32(90, 160, 255, 220), 2.f, ImDrawFlags_RoundCornersAll);
                layer.SetTransparency(255);
            }
            else
                layer.SetTransparency(95);

            if (ImGui::IsItemClicked())
            {
                selectedLayer = static_cast<int>(i);
            }

        }

        if (ImGui::Button("Add Layer"))
        {
            ImGui::OpenPopup("New Layer");
        }

        if (ImGui::Button("Delete Layer"))
        {
            mapEditor.DeleteLayer(selectedLayer);
            selectedLayer = std::max(selectedLayer - 1, 0);
        }

        if (ImGui::BeginPopupModal("New Layer"))
        {
            ImGui::Text("Layer Name : ");
            ImGui::SameLine();
            ImGui::InputText("##", nameLayer, 50, ImGuiInputTextFlags_AutoSelectAll);

            if (ImGui::Button("Create"))
            {
                mapEditor.GetActiveMap()->AddLayer(nameLayer);
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}
