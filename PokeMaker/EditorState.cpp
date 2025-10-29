#include "EditorState.hpp"
#include "tinyfiledialogs.h"
#include <iostream>

EditorState::EditorState() : activeProject(nullptr), createProjectPopupOpen(false), selectedLinkMap(0), selectetExitMap("\0"), selectedLayer(0), selectedMap(0), selectedTileID(0),
selectedTilesetIndex(0), tileSize(32, 32), mapSize(10, 10), windowCenter(0, 0), name("\n"), actionDistance(0.f), collisionMode(false) {}

void EditorState::CloseEditor()
{
    for (Map* map : activeProject->GetMaps())
    {
        delete map;
    }

    std::vector<Tileset*> tilesets = activeProject->GetTilesets();
    for (Tileset* tileset : tilesets)
    {
        delete tileset;
    }
}

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
    windowCenter = ImVec2(window.getSize().x * 0.5f, window.getSize().y * 0.5f);

    camera.Move(dt);

    // Interface ImGui
    ImGui::SetNextWindowPos({ 0,0 });
    ImGui::SetNextWindowSize({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    if (ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar))
    {
        ImGui::DockSpace(ImGui::GetID("DockSpace"), { 0,0 }, ImGuiDockNodeFlags_PassthruCentralNode);
        RenderMainMenu();
    }
    ImGui::End();

    // Si une map est chargée, afficher les widgets
    if (activeProject)
    {
        if (!collisionMode)
        {
            mapEditor.UpdatePlace(dt, window, activeProject, selectedTileID, selectedLayer, selectedTilesetIndex);
            RenderTileSelector();
        }
        else
            mapEditor.UpdateCollision(dt, window, activeProject, selectedLayer);

        RenderLayerPanel();
        RenderProjectPanel();
    }

    if (projectManager.IsNewProject())
    {
        activeProject = projectManager.GetCurrentProject();

        if (activeProject->GetMaps().size() == 0)
            mapEditor.NewMap("Default", { 10, 10 }, { 32, 32 }, activeProject);
        else
            mapEditor.SetActiveMap(activeProject->GetMap("Default"));

        projectManager.ProjectIsLoaded(false);
    }
}

void EditorState::Render(sf::RenderWindow& window)
{
    // Rendu de la carte active
    mapEditor.Render(window, collisionMode, selectedLayer);

    // Rendu final ImGui
    ImGui::SFML::Render(window);

    // Appliquer la vue de la caméra
    camera.Apply(window);
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
            ImGui::MenuItem("Project Panel", nullptr, &showProjectPanel);
            ImGui::EndMenu();
        }

        if (createProjectPopupOpen)
        {
            ImGui::OpenPopup("New project");
            createProjectPopupOpen = false;
        }

        ImGui::SetNextWindowPos(windowCenter, 0, { 0.5f, 0.5f });
        if (ImGui::BeginPopupModal("New project", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
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

    std::vector<Tileset*>& tilesets = activeProject->GetTilesets();
    const char* filters[] = { "*.png", "*.jpeg", "*.jpg" };

    ImGui::Begin("Tile Selector", &showTileSelector);

    if (tilesets.size() != 0)
    {
        if (ImGui::BeginCombo("##TilesetSelector", std::filesystem::path(tilesets[selectedTilesetIndex]->GetPath()).filename().string().c_str()))
        {

            for (int i = 0; i < tilesets.size(); i++)
            {
                ImGui::PushID(i);

                if (ImGui::Selectable(std::filesystem::path(tilesets[i]->GetPath()).filename().string().c_str(), selectedTilesetIndex == i))
                {
                    selectedTilesetIndex = i;
                }

                ImGui::PopID();
            }
            ImGui::EndCombo();
        }

        Tileset* currentTileset = tilesets[selectedTilesetIndex];

        const sf::Texture& tex = currentTileset->GetTexture();
        const ImTextureRef texRef = static_cast<ImTextureRef>(static_cast<intptr_t>(tex.getNativeHandle()));
        const sf::Vector2u texSize = tex.getSize();
        const sf::Vector2i& tileSize = currentTileset->GetTileSize();

        sf::Vector2f tileButtonSize(tileSize);
        int columns = tex.getSize().x / tileSize.x;
        int rows = tex.getSize().y / tileSize.y;

        // Utiliser ImGui::ImageButton pour chaque tile
        if (ImGui::BeginChild("Tileset List Selector", ImVec2(0, 0), ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY,
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove))
        {
            for (int y = 0; y < rows; ++y)
            {
                for (int x = 0; x < columns; ++x)
                {
                    int id = y * columns + x;

                    std::string label("Tile " + std::to_string(id));

                    sf::IntRect rect = currentTileset->GetTileTextureRect(id);
                    ImVec2 pos = ImGui::GetCursorScreenPos();
                    ImVec2 size = { static_cast<float>(tileSize.x), static_cast<float>(tileSize.y) };
                    ImVec2 uv0 = { static_cast<float>(rect.position.x) / texSize.x, static_cast<float>(rect.position.y) / texSize.y };
                    ImVec2 uv1 = { static_cast<float>(rect.position.x + rect.size.x) / texSize.x, static_cast<float>(rect.position.y + rect.size.y) / texSize.y };

                    if (id == selectedTileID)
                        ImGui::Image(texRef, size, uv0, uv1, { 1.f, 1.f, 1.f, 0.5f }, { 0.35f, 0.63f, 1.f, 0.86f });
                    else
                        ImGui::Image(texRef, size, uv0, uv1, { 1.f, 1.f, 1.f, 1.f }, { 0.35f, 0.63f, 1.f, 0.86f });

                    if (ImGui::IsItemHovered())
                    {
                        ImGui::SetTooltip(label.c_str());
                    }

                    ImGui::SetCursorScreenPos(pos);
                    if (ImGui::InvisibleButton(label.c_str(), size))
                    {
                        selectedTileID = id;
                    }

                    if (x < columns - 1)
                        ImGui::SameLine(0.f, -0.5f);
                }
            }
        }
        ImGui::EndChild();
    }
    if (ImGui::Button("Create"))
    {
        ImGui::OpenPopup("New Tileset");
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete"))
    {
        activeProject->DeleteTileset(selectedTilesetIndex);
        selectedTilesetIndex = std::max(selectedTilesetIndex - 1, 0);
    }

    ImGui::SetNextWindowPos(windowCenter, 0, { 0.5f, 0.5f });
    if (ImGui::BeginPopupModal("New Tileset", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
    {
        ImGui::Text("Tile Size : ");
        ImGui::InputInt2("##tileSize", tileSize, ImGuiInputTextFlags_AutoSelectAll);

        if (ImGui::Button("Create"))
        {
            const char* path = tinyfd_openFileDialog("Open tileset...", "../", 0, filters, "Image (*.png, *.jpeg, *.jpg)", 0);
            if (path)
            {
                std::string strPath(path);
                activeProject->LoadTileset(strPath, {tileSize[0], tileSize[1]});
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void EditorState::RenderLayerPanel()
{
    if (!showLayersPanel) return;

    if (ImGui::Begin("Layers Panel", &showLayersPanel))
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
        ImGui::SameLine();
        if (ImGui::Button("Delete Layer"))
        {
            mapEditor.DeleteLayer(selectedLayer);
            selectedLayer = std::max(selectedLayer - 1, 0);
        }

        ImGui::SetNextWindowPos(windowCenter, 0, { 0.5f, 0.5f });
        if (ImGui::BeginPopupModal("New Layer", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
        {
            ImGui::Text("Layer Name : ");
            ImGui::SameLine();
            ImGui::InputText("##", name, 50, ImGuiInputTextFlags_AutoSelectAll);

            if (ImGui::Button("Create"))
            {
                mapEditor.GetActiveMap()->AddLayer(name);
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

void EditorState::RenderProjectPanel()
{
    if (!showProjectPanel) return;

    if (ImGui::Begin("Project Panel", &showProjectPanel))
    {
        ImGui::Text("Project: %s", activeProject->GetName().c_str());

        ImGui::Text("Collision");
        ImGui::SameLine();
        ImGui::Checkbox("##CollisionBox", &collisionMode);

        std::vector<Map*> maps = activeProject->GetMaps();
        if (ImGui::BeginChild("Map Panel", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY,
            ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove))
        {
            if (ImGui::BeginCombo("##MapCombo", mapEditor.GetActiveMap()->GetName().c_str()))
            {
                for (int i = 0; i < maps.size(); i++)
                {
                    ImGui::PushID(i);
                    if (ImGui::Selectable(maps[i]->GetName().c_str(), mapEditor.GetActiveMap() == maps[i]))
                    {
                        mapEditor.SetActiveMap(maps[i]);
                        selectedMap = i;
                    }
                    ImGui::PopID();
                }
                ImGui::EndCombo();
            }

            if (ImGui::Button("Create Map"))
            {
                ImGui::OpenPopup("New Map");
            }
            ImGui::SameLine();
            if (maps.size() > 1)
            {
                if (ImGui::Button("Delete Map"))
                {
                    activeProject->DeleteMap(selectedMap);
                    selectedMap = std::max(selectedMap - 1, 0);
                    mapEditor.SetActiveMap(maps[selectedMap]);
                }
            }

            ImGui::SetNextWindowPos(windowCenter, 0, { 0.5f, 0.5f });
            if (ImGui::BeginPopupModal("New Map", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
            {
                ImGui::Text("Map Name : ");
                ImGui::SameLine();
                ImGui::InputText("##MapName", name, 50, ImGuiInputTextFlags_AutoSelectAll);

                ImGui::Text("Map Size : ");
                ImGui::SameLine();
                ImGui::InputInt2("##MapSize", mapSize, ImGuiInputTextFlags_AutoSelectAll);

                ImGui::Text("Tile Size : ");
                ImGui::SameLine();
                ImGui::InputInt2("##TileSize", tileSize, ImGuiInputTextFlags_AutoSelectAll);

                if (ImGui::Button("Create"))
                {
                    mapEditor.NewMap(std::string(name), { mapSize[0], mapSize[1] }, { tileSize[0], tileSize[1] }, activeProject);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }
        }
        ImGui::EndChild();

        ImGui::Separator();
        
        if (ImGui::BeginChild("LinkMap Panel", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY,
            ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove))
        {
            std::vector<LinkMap>& links = activeProject->GetLinks();
            Map* currentMap = mapEditor.GetActiveMap();

            for (int i = 0; i < links.size(); i++)
            {
                if (links[i].GetEnterMap() != currentMap->GetName() && links[i].GetExitMap() != currentMap->GetName()) continue;

                ImGui::PushID(i);

                if (ImGui::Selectable(std::string(links[i].GetEnterMap() + " -> " + links[i].GetExitMap()).c_str(), selectedLinkMap == i))
                {
                    selectedLinkMap = i;
                }

                ImGui::PopID();
            }

            if (ImGui::Button("Create LinkMap"))
            {
                ImGui::OpenPopup("New LinkMap");
            }
            ImGui::SameLine();
            if (links.size() > 0)
            {
                if (ImGui::Button("Delete LinkMap"))
                {
                    activeProject->DeleteLink(selectedLinkMap);
                    selectedLinkMap = std::max(selectedLinkMap - 1, 0);
                }
            }

            ImGui::SetNextWindowPos(windowCenter, 0, { 0.5f, 0.5f });
            if (ImGui::BeginPopupModal("New LinkMap", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
            {
                if (ImGui::BeginCombo("##MapList", selectetExitMap.c_str()))
                {
                    for (int i = 0; i < maps.size(); i++)
                    {
                        if (maps[i] == currentMap) continue;
                        ImGui::PushID(i);
                        std::string mapName = maps[i]->GetName();
                        if (ImGui::Selectable(mapName.c_str(), selectetExitMap == mapName))
                            selectetExitMap = mapName;
                        ImGui::PopID();
                    }
                    ImGui::EndCombo();
                }

                ImGui::Text("Enter Position : ");
                ImGui::SameLine();
                ImGui::InputInt2("##enter", enterPos, ImGuiInputTextFlags_AutoSelectAll);

                ImGui::Text("Exit Position : ");
                ImGui::SameLine();
                ImGui::InputInt2("##exit", exitPos, ImGuiInputTextFlags_AutoSelectAll);

                ImGui::Text("Action Range : ");
                ImGui::SameLine();
                ImGui::InputFloat("##range", &actionDistance, ImGuiInputTextFlags_AutoSelectAll);

                if (ImGui::Button("Create"))
                {
                    LinkMap link(std::string(currentMap->GetName()), selectetExitMap,
                        sf::Vector2i(enterPos[0], enterPos[1]), sf::Vector2i(exitPos[0], exitPos[1]), actionDistance);
                    activeProject->AddLink(link);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}
