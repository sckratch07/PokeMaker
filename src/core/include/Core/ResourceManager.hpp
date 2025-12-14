#ifndef _CORE_RESOURCEMANAGER_HPP__
#define _CORE_RESOURCEMANAGER_HPP__


#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <string>


namespace Core
{
    /**
    * @brief Gestionnaire centralisé des ressources.
    *
    * Le ResourceManager est responsable du chargement, du stockage
    * et de la distribution des ressources graphiques du moteur :
    * - Textures
    * - Shaders
    *
    * Il garantit :
    * - Une ressource chargée une seule fois
    * - Un accès par identifiant logique (string)
    * - Une gestion claire du cycle de vie
    *
    * Utilisé par :
    * - l'éditeur (tilesets, preview, shaders)
    * - le runtime (sprites, effets visuels)
    */
    class ResourceManager
    {
    public:
        /**
        * @brief Constructeur
        */
        ResourceManager() = default;

        /**
        * @brief Destructeur
        */
        ~ResourceManager() = default;

        /**
        * @brief Charge une texture depuis un fichier
        * @param id Identifiant logique
        * @param filepath Chemin du fichier
        * @return true si le chargement a réussi
        */
        bool loadTexture(const std::string& id, const std::string& filepath);

        /**
        * @brief Récupère une texture chargée
        * @param id Identifiant logique
        */
        sf::Texture& getTexture(const std::string& id);

        /**
        * @brief Vérifie si une texture existe
        */
        bool hasTexture(const std::string& id) const;

        /**
        * @brief Charge un shader depuis des fichiers
        * @param id Identifiant logique
        * @param vertexPath Chemin vertex shader (optionnel)
        * @param fragmentPath Chemin fragment shader
        * @return true si le chargement a réussi
        */
        bool loadShader(const std::string& id,
            const std::string& vertexPath,
            const std::string& fragmentPath);

        /**
        * @brief Récupère un shader
        */
        sf::Shader& getShader(const std::string& id);
        
        /**
        * @brief Vérifie si un shader existe
        */
        bool hasShader(const std::string& id) const;

        /**
        * @brief Libère toutes les ressources
        */
        void clear();

    private:
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
        std::unordered_map<std::string, std::unique_ptr<sf::Shader>> m_shaders;
    };
}


#endif // _CORE_RESOURCEMANAGER_HPP__