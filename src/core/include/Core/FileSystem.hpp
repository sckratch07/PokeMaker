#ifndef _CORE_FILESYSTEM_HPP__
#define _CORE_FILESYSTEM_HPP__

#include <string>
#include <vector>

namespace Core
{
/**
 * @brief Utilitaires de système de fichiers (basés sur std::filesystem).
 *
 * Fournit des fonctions de commodité pour vérifier l'existence, lire
 * des fichiers en texte, lister un répertoire, etc.
 */
class FileSystem
{
public:
    FileSystem() = delete;

    /**
     * @brief Vérifie si un fichier existe.
     */
    static bool exists(const std::string& path);

    /**
     * @brief Lit un fichier texte et renvoie son contenu (vide si échec).
     */
    static std::string readFileToString(const std::string& path);

    /**
     * @brief Liste les fichiers (non récursif) d'un répertoire.
     * @return vecteur de chemins complets (peut être vide).
     */
    static std::vector<std::string> listFiles(const std::string& directory);

    /**
     * @brief Concatène proprement deux segments de chemin.
     */
    static std::string join(const std::string& a, const std::string& b);
};

} // namespace Core

#endif
