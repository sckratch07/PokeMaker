#include "ProjectManager.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <imgui.h>

// Selon ton installation portable-file-dialogs
// #include <portable-file-dialogs.h>

namespace fs = std::filesystem;

namespace Editor {

ProjectManager::ProjectManager(ResourceCache* resourceCache)
    : m_resourceCache(resourceCache)
{
}

// ------------------- PROJET : CREATION -----------------------

bool ProjectManager::CreateNewProject()
{
    std::string folder = OpenFolderDialog();
    if (folder.empty()) return false;

    fs::create_directories(folder + "/Maps");

    m_currentProject = ProjectData{};
    m_currentProject.name = m_tmpProjectName;
    m_currentProject.rootPath = folder;
    m_currentProject.resourcesPath = folder + "/Resources";
    m_currentProject.valid = true;

    fs::create_directory(m_currentProject.resourcesPath);

    SaveProjectJson(folder + "/Project.json");

    std::cout << "[ProjectManager] Nouveau projet créé : " << folder << "\n";
    return true;
}

// ------------------- PROJET : OUVERTURE -----------------------

bool ProjectManager::OpenProjectDialog()
{
    std::string file = OpenFileDialog("*.json");
    if (file.empty()) return false;
    return OpenProject(file);
}

bool ProjectManager::OpenProject(const std::string& projectPath)
{
    if (!LoadProjectJson(projectPath)) {
        std::cerr << "[ProjectManager] Erreur ouverture projet\n";
        return false;
    }

    std::cout << "[ProjectManager] Projet chargé : " << projectPath << "\n";
    return true;
}

// ------------------- PROJET : SAUVEGARDE -----------------------

bool ProjectManager::SaveCurrentProject()
{
    if (!HasProject()) return false;

    const std::string path = m_currentProject.rootPath + "/Project.json";
    return SaveProjectJson(path);
}

bool ProjectManager::SaveProjectAs(const std::string& path)
{
    return SaveProjectJson(path);
}

// ------------------- MAPS -----------------------

bool ProjectManager::LoadMap(const std::string& mapFile)
{
    if (!HasProject()) return false;

    MapSerializer serializer(m_resourceCache);
    auto map = std::make_unique<Map>();

    if (!serializer.LoadMap(m_currentProject.rootPath + "/Maps/" + mapFile, *map)) {
        std::cerr << "[ProjectManager] Impossible de charger map : " << mapFile << "\n";
        return false;
    }

    m_loadedMapFile = mapFile;
    m_currentMap = std::move(map);

    std::cout << "[ProjectManager] Map chargée : " << mapFile << "\n";
    return true;
}

bool ProjectManager::CreateNewMap(const std::string& name)
{
    if (!HasProject()) return false;

    std::string filename = name + ".map.json";
    fs::path filepath = m_currentProject.rootPath + "/Maps/" + filename;

    Map map;
    map.name = name;

    MapSerializer serializer(m_resourceCache);
    if (!serializer.SaveMap(filepath.string(), map)) {
        return false;
    }

    m_currentProject.mapFiles.push_back(filename);
    SaveCurrentProject();

    std::cout << "[ProjectManager] Nouvelle map créée : " << filename << "\n";
    return true;
}

bool ProjectManager::SaveMap(Map& map)
{
    if (!HasProject() || m_loadedMapFile.empty()) return false;

    MapSerializer serializer(m_resourceCache);
    return serializer.SaveMap(
        m_currentProject.rootPath + "/Maps/" + m_loadedMapFile,
        map
    );
}

// ------------------- JSON Projet -----------------------

bool ProjectManager::LoadProjectJson(const std::string& file)
{
    if (!fs::exists(file)) return false;

    std::ifstream in(file);
    nlohmann::json json;
    in >> json;

    m_currentProject = ProjectData{};
    m_currentProject.name = json.value("name", "UnnamedProject");
    m_currentProject.rootPath = fs::path(file).parent_path().string();
    m_currentProject.resourcesPath = json.value("resourcesPath", "");
    m_currentProject.mapFiles = json.value("maps", std::vector<std::string>{});
    m_currentProject.valid = true;

    return true;
}

bool ProjectManager::SaveProjectJson(const std::string& file)
{
    nlohmann::json json;
    json["name"] = m_currentProject.name;
    json["resourcesPath"] = m_currentProject.resourcesPath;
    json["maps"] = m_currentProject.mapFiles;

    std::ofstream out(file);
    out << json.dump(4);

    return true;
}

// ------------------- DIALOGS -----------------------

std::string ProjectManager::OpenFileDialog(const char* filter)
{
    // Placeholder -> tu brancheras portable-file-dialogs :
    // pfd::open_file("Ouvrir projet", "", { filter }).result();
    return ""; 
}

std::string ProjectManager::OpenFolderDialog()
{
    return ""; 
}

std::string ProjectManager::SaveFileDialog(const char* filter)
{
    return "";
}

// ------------------- UPDATE & UI -----------------------

void ProjectManager::Update(sf::Time)
{
}

void ProjectManager::RenderUI()
{
    if (!m_showProjectWindow) return;

    ImGui::Begin("Projet", &m_showProjectWindow);

    if (!HasProject())
    {
        ImGui::InputText("Nom du projet", m_tmpProjectName, 128);

        if (ImGui::Button("Créer nouveau projet"))
            CreateNewProject();

        if (ImGui::Button("Ouvrir projet"))
            OpenProjectDialog();
    }
    else
    {
        ImGui::Text("Projet : %s", m_currentProject.name.c_str());
        ImGui::Separator();

        if (ImGui::Button("Sauvegarder projet"))
            SaveCurrentProject();

        ImGui::InputText("Nouvelle map", m_tmpMapName, 128);

        if (ImGui::Button("Créer map"))
            CreateNewMap(m_tmpMapName);

        ImGui::Separator();

        ImGui::Text("Maps existantes :");
        for (auto& f : m_currentProject.mapFiles)
        {
            if (ImGui::Selectable(f.c_str()))
                LoadMap(f);
        }
    }

    ImGui::End();
}

} // namespace Editor
