#include "ProjectManager.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using json = nlohmann::json;

bool ProjectManager::CreateProject(const std::string& name, const std::string& path)
{
    try {
        // Création du répertoire de base du projet
        if (!fs::exists(path)) {
            fs::create_directories(path);
        }

        currentProject = Project(name, path);

        // Création d’un fichier de base du projet (vide au début)
        return SaveProject(path + "/" + name + ".json");
    }
    catch (const std::exception& e) {
        std::cerr << "[ProjectManager] Erreur lors de la création du projet : " << e.what() << std::endl;
        return false;
    }
}

bool ProjectManager::LoadProject(const std::string& path)
{
    try {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "[ProjectManager] Impossible d’ouvrir le fichier : " << path << std::endl;
            return false;
        }

        json data;
        file >> data;
        file.close();

        currentProject.Deserialize(data);

        std::cout << "[ProjectManager] Projet chargé depuis " << path << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "[ProjectManager] Erreur lors du chargement : " << e.what() << std::endl;
        return false;
    }
}

bool ProjectManager::SaveProject(const std::string& path)
{
    try {
        json data = currentProject.Serialize();

        std::ofstream file(path);
        if (!file.is_open()) {
            std::cerr << "[ProjectManager] Impossible d’écrire dans le fichier : " << path << std::endl;
            return false;
        }

        // Sauvegarde avec plus de lisibilité
        file << data.dump(4);
        file.close();

        std::cout << "[ProjectManager] Projet sauvegardé : " << path << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "[ProjectManager] Erreur lors de la sauvegarde : " << e.what() << std::endl;
        return false;
    }
}

Project& ProjectManager::GetCurrentProject()
{
    return currentProject;
}
