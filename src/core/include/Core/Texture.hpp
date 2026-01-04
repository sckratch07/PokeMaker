#ifndef _CORE_TEXTURE_HPP__
#define _CORE_TEXTURE_HPP__

#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace Core
{
    struct Texture
    {
        Texture(std::string name, std::shared_ptr<sf::Texture> texture)
            : m_name(name), m_texture(texture)
        {
            m_textSize = m_texture->getSize();
        }

        std::string m_name = "No Name.";
        std::shared_ptr<sf::Texture> m_texture;
        sf::Vector2u m_textSize = {0, 0};
    };
}

#endif