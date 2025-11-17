#ifndef _CORE_RESOURCE_MANAGER_HPP__
#define _CORE_RESOURCE_MANAGER_HPP__

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

namespace Core
{
    class ResourceManager
    {
    public:
        ResourceManager() = default;
        ~ResourceManager() = default;

        // Textures
        std::shared_ptr<sf::Texture> LoadTexture(const std::string& path);
        std::shared_ptr<sf::Texture> GetTexture(const std::string& path) const;

        void clear();
    private:
        std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
    };
} // namespace Core

#endif
