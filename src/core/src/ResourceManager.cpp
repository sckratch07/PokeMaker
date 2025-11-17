#include <ResourceManager.hpp>
#include <Logger.hpp>

namespace Core
{
    std::shared_ptr<sf::Texture> ResourceManager::loadTexture(const std::string& path)
    {
        auto it = m_textures.find(path);
        if (it != m_textures.end()) {
            return it->second;
        }

        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(path)) {
            log("Failed to load texture: " + path, LogLevel::Error);
            return nullptr;
        }

        m_textures[path] = texture;
        log("Loaded texture: " + path, LogLevel::Info);
        return texture;
    }

    std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string& path) const
    {
        auto it = m_textures.find(path);
        if (it != m_textures.end()) {
            return it->second;
        }
       log("Texture not found: " + path, LogLevel::Warning);
       return nullptr;
    }

    void ResourceManager::clear() {
       m_textures.clear();
       log("All textures cleared", LogLevel::Info);
    }
} // namespace Core
