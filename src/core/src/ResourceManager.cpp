#include "ResourceManager.hpp"
#include "Logger.hpp"

namespace Core
{
    std::shared_ptr<sf::Texture> ResourceManager::LoadTexture(const std::string& path)
    {
        auto it = m_textures.find(path);
        if (it != m_textures.end()) {
            return it->second;
        }

        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(path)) {
            Log("Failed to load texture: " + path, LogLevel::Error);
            return nullptr;
        }

        m_textures[path] = texture;
        Log("Loaded texture: " + path, LogLevel::Info);
        return texture;
    }

    std::shared_ptr<sf::Texture> ResourceManager::GetTexture(const std::string& path) const
    {
        auto it = m_textures.find(path);
        if (it != m_textures.end()) {
            return it->second;
        }
       Log("Texture not found: " + path, LogLevel::Warning);
       return nullptr;
    }

    void ResourceManager::clear() {
       m_textures.clear();
       Log("All textures cleared", LogLevel::Info);
    }
} // namespace Core
