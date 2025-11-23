#include "Renderer/GridRenderer.hpp"

namespace Renderer
{

    GridRenderer::GridRenderer(Renderer& renderer)
        : m_renderer(renderer), m_vertices(sf::PrimitiveType::Lines)
    {
    }

    void GridRenderer::configure(int cellSize, int width, int height)
    {
        m_cellSize = cellSize;
        m_width = width;
        m_height = height;

        m_vertices.clear();

        // Lignes verticales
        for (int x = 0; x <= m_width; ++x)
        {
            float xPos = static_cast<float>(x * m_cellSize);

            sf::Vertex vertex1;
            vertex1.position = { xPos, 0.f };
            vertex1.color = sf::Color(255, 255, 255, 60);
            m_vertices.append(vertex1);

            sf::Vertex vertex2;
            vertex2.position = { xPos, static_cast<float>(m_height * m_cellSize) };
            vertex2.color = sf::Color(255, 255, 255, 60);
            m_vertices.append(vertex2);
        }

        // Lignes horizontales
        for (int y = 0; y <= m_height; ++y)
        {
            float yPos = static_cast<float>(y * m_cellSize);

            sf::Vertex vertex1;
            vertex1.position = { 0.f, yPos };
            vertex1.color = sf::Color(255, 255, 255, 60);
            m_vertices.append(vertex1);

            sf::Vertex vertex2;
            vertex2.position = { static_cast<float>(m_width * m_cellSize), yPos };
            vertex2.color = sf::Color(255, 255, 255, 60);
            m_vertices.append(vertex2);
        }
    }

    void GridRenderer::draw()
    {
        m_renderer.draw(m_vertices);
    }

} // namespace Renderer
