#include "ProjectManager.hpp"
#include <fstream>

namespace fs = std::filesystem;

bool ProjectManager::CreateProject(const std::string& name, const std::string& path)
{
    try {
        // Création du répertoire de base du projet
        if (!fs::exists(path))
        {
            fs::create_directories(path);
        }
        fs::create_directories(path + "/assets");

        currentProject = Project(name, path);

        newProject = true;

        // Création d’un fichier de base du projet (vide au début)
        return SaveProject(path + static_cast<char>(92) + name + ".json");
    }
    catch (const std::exception& e) {
        std::cerr << "[ProjectManager] Erreur lors de la creation du projet : " << e.what() << std::endl;
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

        newProject = true;

        std::cout << "[ProjectManager] Projet charge depuis " << path << std::endl;
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
            std::cerr << "[ProjectManager] Impossible d’ecrire dans le fichier : " << path << std::endl;
            return false;
        }

        // Sauvegarde avec plus de lisibilité
        file << data.dump(4);
        file.close();

        std::cout << "[ProjectManager] Projet sauvegarde : " << path << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "[ProjectManager] Erreur lors de la sauvegarde : " << e.what() << std::endl;
        return false;
    }
}
