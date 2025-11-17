#ifndef _ENGINE_LAYER_HPP__
#define _ENGINE_LAYER_HPP__

#include <Tile.hpp>
#include <Tileset.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace Engine
{
    enum class LayerType
    {
        Background,
        Ground,
        Collision,
        Objects,
        Lighting
    };

    class Layer : public sf::Drawable
    {
    public:
        Layer() = default;
        Layer(int width, int height, LayerType type = LayerType::Ground);
        ~Layer() = default;

        void setTile(int x, int y, int tileId);
        int getTile(int x, int y) const;
        void setTileset(std::shared_ptr<Tileset> tileset);

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        LayerType getType() const { return m_type; }

       void update(float dt); // animation
    protected:
       void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
       int m_width = 0;
       int m_height = 0;
       LayerType m_type = LayerType::Ground;
       std::vector<int> m_tiles;                   // ID de chaque tile
       std::shared_ptr<Tileset> m_tileset;

       std::vector<float> m_frameTimers;           // pour l’animation des tiles
    };
} // namespace Engine

#endif
