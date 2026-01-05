#ifndef _CORE_TEXTURE_COMPONENT_HPP__
#define _CORE_TEXTURE_COMPONENT_HPP__

#include "Core/Texture.hpp"

namespace Core
{
    struct TextureComponent
    {
        TextureComponent() = default;
        explicit TextureComponent(std::shared_ptr<Texture> texture) : m_texture(texture) {}

        std::shared_ptr<Texture> m_texture = nullptr;
    };
}

#endif