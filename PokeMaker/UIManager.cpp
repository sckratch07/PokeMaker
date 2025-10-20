#include "UIManager.hpp"
#include "tinyfiledialogs.h"
#include <string>
#include <filesystem>

UIManager::UIManager() : selectedTileID(-1), selectedLayer(0), selectedProjectPath("")
{
    newProjectPath[0] = '\0';
}

void UIManager::RenderMainMenu(ProjectManager& projectManager)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Fichier"))
        {
            if (ImGui::MenuItem("Nouveau"))
            {
                createProjectPopupOpen = true;
            }
            if (ImGui::MenuItem("Ouvrir"))
            {
                const char* path = tinyfd_selectFolderDialog("Ouvrir un projet...", "../");
                if (path)
                    projectManager.LoadProject(std::string(path) + "/" + std::filesystem::path(path).stem().string() + ".json");
            }
            if (ImGui::MenuItem("Sauvegarder"))
            {
                std::filesystem::path path = projectManager.GetCurrentProject()->GetBasePath();
                projectManager.SaveProject(path.string() + "/" + path.stem().string() + ".json");
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Affichage"))
        {
            ImGui::MenuItem("Selecteur de tuiles", nullptr, &showTileSelector);
            ImGui::MenuItem("Calques", nullptr, &showLayersPanel);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // Popup de création de projet
    if (createProjectPopupOpen)
    {
        ImGui::OpenPopup("Creer un nouveau projet");
        createProjectPopupOpen = false;
    }

    if (ImGui::BeginPopupModal("Creer un nouveau projet", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::Button("Creer"))
        {
            const char* path = tinyfd_selectFolderDialog("Ouvrir un projet...", std::string("../").c_str());
            if (path)
            {
                selectedProjectPath = std::string(path);
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Annuler"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void UIManager::RenderTileSelector(Map* activeMap, int* currentTilesetIndex)
{
    if (!showTileSelector) return;

    std::vector<Tileset> tilesets = activeMap->GetTilesets();
    const char* filters[] = {"*.png", "*.jpeg", "*.jpg"};

    ImGui::Begin("Selecteur de tuiles", &showTileSelector);

    if (tilesets.size() > 1)
        ImGui::SliderInt("Tileset: ", currentTilesetIndex, 0, (int)tilesets.size() - 1);

    Tileset currentTileset = tilesets[*currentTilesetIndex];
    
    const sf::Texture& tex = currentTileset.GetTexture();
    const sf::Vector2i& tileSize = currentTileset.GetTileSize();

    sf::Vector2f tileButtonSize(tileSize);
    int columns = tex.getSize().x / tileSize.x;
    int rows = tex.getSize().y / tileSize.y;

    ImGui::Text("Tileset : %s", currentTileset.GetPath().c_str());
    ImGui::Separator();

    // Utiliser ImGui::ImageButton pour chaque tile
    sf::Sprite sprt(tex);
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < columns; ++x)
        {
            int id = y * columns + x;

            sf::IntRect rect = currentTileset.GetTileTextureRect(id);
            sprt.setTextureRect(rect);

            if (ImGui::ImageButton(std::string("##Tile" + std::to_string(id)).c_str(), sprt, tileButtonSize,
                sf::Color::Transparent,
                selectedTileID == id ? sf::Color::Transparent : sf::Color::White))
            {
                selectedTileID = id;
            }

            if (x < columns - 1)
                ImGui::SameLine(0.0f, 0.1f);
        }
    }
    ImGui::Separator();
    if (ImGui::Button("Create"))
    {
        const char* path = tinyfd_openFileDialog("Ouvrir une tileset...", "../", 0, filters, "Image (*.png, *.jpeg, *.jpg)", 0);
        if (path)
        {
            Tileset newTileset;
            if (newTileset.LoadFromFile(path))
            {
                newTileset.Deserialize({ {"tileSize", {tileSize.x, tileSize.y}} });
                activeMap->AddTileset(newTileset);
            }
        }
    }
    if (tilesets.size() > 1)
    {
        ImGui::SameLine();
        if (ImGui::Button("Delete")&&)
        {
            activeMap.
        }
    }

    ImGui::End();
}

void UIManager::RenderLayerPanel(std::vector<Layer>& layers)
{
    if (!showLayersPanel) return;

    ImGui::Begin("Calques", &showLayersPanel);

    for (size_t i = 0; i < layers.size(); ++i)
    {
        Layer& layer = layers[i];
        std::string label = layer.GetName() + "##" + std::to_string(i);

        bool visible = layer.IsVisible();
        if (ImGui::Checkbox(label.c_str(), &visible))
        {
            layer.SetVisible(visible);
        }

        if (ImGui::IsItemClicked())
        {
            selectedLayer = (int)(i);
        }
    }
    ImGui::End();
}

void UIManager::HandleMenuActions(ProjectManager& projectManager)
{
    if (!selectedProjectPath.empty())
    {
        std::string path = selectedProjectPath;
        std::string name = std::filesystem::path(path).stem().string();

        if (!std::filesystem::exists(path))
            std::filesystem::create_directories(path);

        if (projectManager.CreateProject(name, path))
            std::cout << "[UIManager] Projet cree : " << name << " a " << path << std::endl;
        else
            std::cerr << "[UIManager] Echec de la creation du projet." << std::endl;

        // reset des champs
        selectedProjectPath.clear();
        newProjectPath[0] = '\0';
    }
}
