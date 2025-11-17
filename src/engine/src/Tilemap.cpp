#include <Tilemap.hpp>
#include <Logger.hpp>

namespace Engine
{
    Tilemap::Tilemap(int width, int height)
        : m_width(width), m_height(height) {}

    void Tilemap::setTileset(std::shared_ptr<Tileset> tileset)
    {
        m_tileset = tileset;
        for (std::shared_ptr<Layer>& layer : m_layers)
        {
            layer->setTileset(tileset);
        }
    }

    void Tilemap::addLayer(LayerType type)
    {
        std::shared_ptr<Layer> existing = findLayer(type);
        if (existing)
        {
            Core::log("Layer already exists, skipping duplicate.", Core::LogLevel::Warning);
            return;
        }

        std::shared_ptr<Layer> layer = std::make_shared<Layer>(m_width, m_height, type);
        layer->setTileset(m_tileset);
        m_layers.push_back(layer);
    }

    std::shared_ptr<Layer> Tilemap::findLayer(LayerType type) const
    {
        for (const std::shared_ptr<Layer>& layer : m_layers)
        {
            if (layer->getType() == type)
                return layer;
        }
        return nullptr;
    }

    Layer* Tilemap::getLayer(LayerType type)
    {
        std::shared_ptr<Layer> layer = findLayer(type);
        return layer ? layer.get() : nullptr;
    }

    const Layer* Tilemap::getLayer(LayerType type) const
    {
        std::shared_ptr<Layer> layer = findLayer(type);
        return layer ? layer.get() : nullptr;
    }

    void Tilemap::setTile(LayerType layerType, int x, int y, int tileId)
    {
        std::shared_ptr<Layer> layer = findLayer(layerType);
        if (!layer) return;
        layer->setTile(x, y, tileId);
    }

    int Tilemap::getTile(LayerType layerType, int x, int y) const
    {
        std::shared_ptr<Layer> layer = findLayer(layerType);
        return layer ? layer->getTile(x, y) : -1;
    }

    void Tilemap::update(float dt)
    {
        for (std::shared_ptr<Layer>& layer : m_layers)
            layer->update(dt);
    }

    void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const std::shared_ptr<Layer>& layer : m_layers)
            target.draw(*layer, states);
    }

    json Tilemap::toJson() const
    {
        json j;

        j["width"]  = m_width;
        j["height"] = m_height;

        if (m_tileset)
        {
            j["tileset"]["path"] = "";  // L'éditeur remplira ce champ
            j["tileset"]["tileWidth"]  = m_tileset->getTile(0).textureRect.size.x;
            j["tileset"]["tileHeight"] = m_tileset->getTile(0).textureRect.size.y;
        }

        for (const std::shared_ptr<Layer>& layer : m_layers)
        {
            json l;
            l["type"] = static_cast<int>(layer->getType());
            l["tiles"] = {};

            for (int y = 0; y < m_height; ++y)
            {
                for (int x = 0; x < m_width; ++x)
                {
                    l["tiles"].push_back(layer->getTile(x, y));
                }
            }
            j["layers"].push_back(l);
        }

        return j;
    }

    bool Tilemap::loadFromJson(const json& data)
    {
        try
        {
            m_width = data.at("width").get<int>();
            m_height = data.at("height").get<int>();

            m_layers.clear();

            for (const json& layerData : data.at("layers"))
            {
                LayerType type = static_cast<LayerType>(layerData.at("type").get<int>());
                addLayer(type);

                std::shared_ptr<Layer> layer = findLayer(type);
                if (!layer) continue;

                const json& tiles = layerData.at("tiles");
                int index = 0;

                for (int y = 0; y < m_height; ++y)
                {
                    for (int x = 0; x < m_width; ++x)
                    {
                        int tileId = tiles[index++].get<int>();
                        layer->setTile(x, y, tileId);
                    }
                }
            }

            return true;
        }
        catch (const std::exception& e)
        {
            Core::log(std::string("Tilemap JSON load error: ") + e.what(), Core::LogLevel::Error);
            return false;
        }
    }
} // namaspace Engine
