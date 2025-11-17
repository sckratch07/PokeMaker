#ifndef _ENGINE_TILEMAP_HPP__
#define _ENGINE_TILEMAP_HPP__

#include <Layer.hpp>
#include <Tileset.hpp>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

using json = nlohmann::json;

namespace Engine
{
    class Tilemap : public sf::Drawable
    {
    public:
        Tilemap() = default;
        Tilemap(int width, int height);
        ~Tilemap() = default;

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

        void addLayer(LayerType type);
        Layer* getLayer(LayerType type);
        const Layer* getLayer(LayerType type) const;

        const std::vector<std::shared_ptr<Layer>>& getLayers() const { return m_layers; }

        void setTileset(std::shared_ptr<Tileset> tileset);
        std::shared_ptr<Tileset> getTileset() const { return m_tileset; }

        void setTile(LayerType layerType, int x, int y, int tileId);
        int getTile(LayerType layerType, int x, int y) const;

        // --- Update (animations, etc.) ---
        void update(float dt);

        // --- Serialization ---
        json toJson() const;
        bool loadFromJson(const json& data);

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        int m_width = 0;
        int m_height = 0;

        std::shared_ptr<Tileset> m_tileset;
        std::vector<std::shared_ptr<Layer>> m_layers;

        // Fonction utilitaire pour trouver un layer par type
        std::shared_ptr<Layer> findLayer(LayerType type) const;
    };

} // namespace Engine

#endif
