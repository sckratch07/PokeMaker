#ifndef _RENDERER_RENDERER_HPP__
#define _RENDERER_RENDERER_HPP__

#include "Renderer/RenderWindow.hpp"
#include "Renderer/Camera.hpp"
#include <SFML/Graphics/Drawable.hpp>

namespace Renderer
{

    /**
     * @class Renderer
     * @brief Gestionnaire principal de rendu.
     *
     * Cette classe coordonne la fenêtre de rendu, la caméra et
     * fournit des fonctions utilitaires pour dessiner des éléments
     * graphiques dans la scène.
     *
     * Les sous-systèmes comme TileRenderer ou GridRenderer utilisent
     * cette classe pour effectuer leur rendu dans la fenêtre.
     */
    class Renderer
    {
    public:
        /**
         * @brief Construit le Renderer et initialise les composants internes.
         */
        Renderer();

        /**
         * @brief Initialise le renderer avec une fenêtre.
         *
         * @param title Titre de la fenêtre.
         * @param width Largeur en pixels.
         * @param height Hauteur en pixels.
         */
        void initialize(const std::string& title, unsigned int width, unsigned int height);

        /**
         * @brief Nettoie la fenêtre avant le rendu de la frame.
         *
         * @param color Couleur utilisée pour effacer la fenêtre.
         */
        void clear(const sf::Color& color = sf::Color::Black);

        /**
         * @brief Affiche la frame dans la fenêtre.
         */
        void display();

        /**
         * @brief Dessine un objet SFML.
         *
         * @param drawable Objet graphique à afficher.
         */
        void draw(const sf::Drawable& drawable);

        /**
         * @brief Accède à la fenêtre de rendu.
         *
         * @return Référence à RenderWindow.
         */
        RenderWindow& getWindow();

        /**
         * @brief Accède à la caméra.
         *
         * @return Référence à Camera.
         */
        Camera& getCamera();

    private:
        RenderWindow m_window; ///< Fenêtre de rendu principale.
        Camera m_camera;       ///< Caméra permettant la navigation dans la scène.
    };

} // namespace Renderer

#endif
