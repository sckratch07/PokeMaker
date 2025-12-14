#include "Core/ResourceManager.hpp"
#include <stdexcept>

namespace Core
{
    bool ResourceManager::loadTexture(const std::string& id, const std::string& filepath)
    {
        if (m_textures.find(id) != m_textures.end())
            return true;

        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(filepath))
            return false;

        m_textures[id] = std::move(texture);
        return true;
    }

    sf::Texture& ResourceManager::getTexture(const std::string& id)
    {
        if (m_textures.find(id) == m_textures.end())
            throw std::runtime_error("Texture not found: " + id);
        return *m_textures[id];
    }

    bool ResourceManager::hasTexture(const std::string& id) const
    {
        return (m_textures.find(id) == m_textures.end());
    }

    bool ResourceManager::loadShader(const std::string& id,
        const std::string& vertexPath,
        const std::string& fragmentPath)
    {
        if (m_shaders.find(id) != m_shaders.end())
            return true;

        auto shader = std::make_unique<sf::Shader>();

        bool success = false;
        if (!vertexPath.empty())
        {
            success = shader->loadFromFile(vertexPath, fragmentPath);
        }
        else
        {
            success = shader->loadFromFile(fragmentPath, sf::Shader::Type::Fragment);
        }

        if (!success)
            return false;
        m_shaders[id] = std::move(shader);
        return true;
    }

    sf::Shader& ResourceManager::getShader(const std::string& id)
    {
        if (m_shaders.find(id) == m_shaders.end())
            throw std::runtime_error("Shader not found: " + id);
        return *m_shaders[id];
    }

    bool ResourceManager::hasShader(const std::string& id) const
    {
        return (m_shaders.find(id) == m_shaders.end());
    }

    void ResourceManager::clear()
    {
        m_textures.clear();
        m_shaders.clear();
    }
}