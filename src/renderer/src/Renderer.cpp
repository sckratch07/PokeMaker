#include "Renderer/Renderer.hpp"

namespace Renderer
{

    Renderer::Renderer()
    {
        // Constructeur vide : l'initialisation vient après
    }

    void Renderer::initialize(const std::string& title, unsigned int width, unsigned int height)
    {
        m_window.create(title, width, height);

        // Associer la caméra à la fenêtre
        m_window.getSFMLWindow().setView(m_camera.getView());
    }

    void Renderer::clear(const sf::Color& color)
    {
        m_window.clear(color);
    }

    void Renderer::display()
    {
        // Mise à jour de la vue avant affichage
        m_window.getSFMLWindow().setView(m_camera.getView());
        m_window.display();
    }

    void Renderer::draw(const sf::Drawable& drawable)
    {
        m_window.getSFMLWindow().draw(drawable);
    }

    RenderWindow& Renderer::getWindow()
    {
        return m_window;
    }

    Camera& Renderer::getCamera()
    {
        return m_camera;
    }

} // namespace Renderer
