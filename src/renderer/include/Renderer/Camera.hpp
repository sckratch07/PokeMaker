#ifndef _RENDERER_CAMERA_HPP__
#define _RENDERER_CAMERA_HPP__

#include <SFML/Graphics/View.hpp>

namespace Renderer
{

    /**
     * @class Camera
     * @brief Caméra 2D permettant de contrôler la vue dans la scène.
     *
     * Cette classe encapsule sf::View et permet de gérer le déplacement,
     * le zoom, et la position de la caméra dans le monde du jeu. Elle est
     * utilisée par le système Renderer pour afficher correctement la scène.
     */
    class Camera
    {
    public:
        /**
         * @brief Constructeur par défaut.
         *
         * Initialise une vue centrée en (0,0) avec une taille par défaut.
         */
        Camera();

        /**
         * @brief Définit la position de la caméra dans le monde.
         *
         * @param x Position horizontale.
         * @param y Position verticale.
         */
        void setPosition(float x, float y);

        /**
         * @brief Déplace la caméra d'un certain offset.
         *
         * @param dx Déplacement horizontal.
         * @param dy Déplacement vertical.
         */
        void move(float dx, float dy);

        /**
         * @brief Applique un zoom à la vue.
         *
         * @param factor Facteur de zoom (ex: 1.1 pour zoomer, 0.9 pour dézoomer).
         */
        void zoom(float factor);

        /**
         * @brief Récupère la vue SFML sous-jacente.
         *
         * @return Référence à sf::View.
         */
        sf::View& getView();

    private:
        sf::View m_view; ///< Vue SFML utilisée pour la caméra.
    };

} // namespace Renderer

#endif
