#ifndef _RENDERER_RENDERWINDOW_HPP__
#define _RENDERER_RENDERWINDOW_HPP__

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>

namespace Renderer
{

    /**
     * @class RenderWindow
     * @brief Classe responsable de la gestion de la fenêtre de rendu SFML.
     *
     * Cette classe encapsule sf::RenderWindow afin d'offrir une interface
     * plus propre, centralisée et adaptée à l'architecture du moteur.
     * Elle gère la création, l'affichage, les événements et les opérations
     * de rendu générales.
     */
    class RenderWindow
    {
    public:
        /**
         * @brief Construit une fenêtre vide (non créée).
         */
        RenderWindow() = default;

        /**
         * @brief Crée la fenêtre SFML avec un titre et une taille.
         *
         * @param title Titre de la fenêtre.
         * @param width Largeur de la fenêtre.
         * @param height Hauteur de la fenêtre.
         */
        void create(const std::string& title, unsigned int width, unsigned int height);

        /**
         * @brief Vide la fenêtre avec une couleur spécifique.
         *
         * @param color Couleur utilisée pour nettoyer la fenêtre.
         */
        void clear(const sf::Color& color = sf::Color::Black);

        /**
         * @brief Affiche le contenu rendu à l'écran.
         */
        void display();

        /**
         * @brief Vérifie si la fenêtre est ouverte.
         *
         * @return true si la fenêtre est ouverte.
         */
        bool isOpen() const;

        /**
         * @brief Ferme la fenêtre.
         */
        void close();

        /**
         * @brief Accède à la fenêtre SFML sous-jacente.
         *
         * Utile lorsque des systèmes doivent effectuer des opérations
         * directes avec SFML (dessins personnalisés, ImGui-SFML, etc.).
         *
         * @return Référence vers sf::RenderWindow.
         */
        sf::RenderWindow& getSFMLWindow();

    private:
        sf::RenderWindow m_window; ///< Fenêtre SFML utilisée pour le rendu.
    };

} // namespace Renderer

#endif
