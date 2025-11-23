#include "Renderer/RenderWindow.hpp"

namespace Renderer
{

    void RenderWindow::create(const std::string& title, unsigned int width, unsigned int height)
    {
        m_window.create(sf::VideoMode(sf::Vector2u(width, height)), title);
    }

    void RenderWindow::clear(const sf::Color& color)
    {
        m_window.clear(color);
    }

    void RenderWindow::display()
    {
        m_window.display();
    }

    bool RenderWindow::isOpen() const
    {
        return m_window.isOpen();
    }

    void RenderWindow::close()
    {
        m_window.close();
    }

    sf::RenderWindow& RenderWindow::getSFMLWindow()
    {
        return m_window;
    }

} // namespace Renderer
