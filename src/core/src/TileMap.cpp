#include "Core/TileMap.hpp"

#include <iostream>

namespace Core
{
    bool TileMap::AddLayer(const char* layerName)
    {
        m_layers.push_back(Layer(layerName, m_width, m_height));
        return true;
    }

    bool TileMap::RemoveLayer(const std::string layerName)
    {
        for (auto& layer : m_layers)
        {
            if (layer.m_name == layerName)
            {
                std::swap(layer, m_layers.back());
                m_layers.pop_back();
                return true;
            }
        }
        return false;
    }
}