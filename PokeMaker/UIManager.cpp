#include "UIManager.hpp"
#include "tinyfiledialogs.h"
#include <filesystem>

UIManager::UIManager() : selectedTileID(-1), selectedLayer(0), selectedProjectPath("")
{
    newProjectPath[0] = '\0';
}

void UIManager::RenderMainMenu(ProjectManager& projectManager)
{
    const char* filter[] = { "" };
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
            ImGui::MenuItem("Proprietes", nullptr, &showPropertiesPanel);
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

void UIManager::RenderTileSelector(Tileset& tileset)
{
    if (!showTileSelector) return;

    ImGui::Begin("Selecteur de tuiles", &showTileSelector);

    const sf::Texture& tex = tileset.GetTexture();
    const sf::Vector2i& tileSize = tileset.GetTileSize();

    ImVec2 tileButtonSize((float)tileSize.x, (float)tileSize.y);
    int columns = tex.getSize().x / tileSize.x;
    int rows = tex.getSize().y / tileSize.y;

    ImGui::Text("Tileset : %s", tileset.GetName().c_str());
    ImGui::Separator();

    // Utiliser ImGui::ImageButton pour chaque tile
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < columns; ++x)
        {
            int id = y * columns + x;

            sf::IntRect rect = tileset.GetTileTextureRect(id);
            ImVec2 uv0(
                rect.position.x / (float)tex.getSize().x,
                rect.position.y / (float)tex.getSize().y
            );
            ImVec2 uv1(
                (rect.position.x + rect.size.x) / (float)tex.getSize().x,
                (rect.position.y + rect.size.y) / (float)tex.getSize().y
            );

            if (ImGui::ImageButton(std::string("%d/%d", x, y).c_str(), (ImTextureID)tex.getNativeHandle(), tileButtonSize, uv0, uv1))
            {
                selectedTileID = id;
            }

            if (x < columns - 1)
                ImGui::SameLine();
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

void UIManager::RenderPropertiesPanel(Tile* selectedTile)
{
    if (!showPropertiesPanel) return;

    ImGui::Begin("Propriétés", &showPropertiesPanel);

    if (selectedTile)
    {
        ImGui::Text("Position : %d, %d", selectedTile->GetPosition().x, selectedTile->GetPosition().y);
        bool collidable = selectedTile->IsCollidable();
        if (ImGui::Checkbox("Collision", &collidable))
        {
            selectedTile->SetCollidable(collidable);
        }
    }
    else
        ImGui::Text("Aucune tuile sélectionnée.");
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
            std::cout << "[UIManager] Projet cree : " << name << " à " << path << std::endl;
        else
            std::cerr << "[UIManager] Echec de la creation du projet." << std::endl;

        // reset des champs
        selectedProjectPath.clear();
        newProjectPath[0] = '\0';
    }
}
