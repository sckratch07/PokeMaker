#ifndef _CORE_STATE_HPP__
#define _CORE_STATE_HPP__

#include <SFML/Graphics.hpp>
#include <string>

namespace Core
{
    class CoreEngine;
    
    /**
    * @brief Classe abstraite représentant un State.
    *
    * Un State représente un contexte logique unique de l'application :
    * - Menu principal
    * - Éditeur de map
    * - Jeu (runtime)
    * - Chargement / splash screen
    *
    * Chaque State est responsable de :
    * - Sa logique interne
    * - Son rendu
    * - La gestion de ses événements
    *
    * Les States sont manipulés exclusivement par la StateMachine.
    */
    class State
    {
    public:
        /**
        * @brief Constructeur
        * @param core Référence vers le moteur central
        */
        explicit State(CoreEngine& core);

        /**
        * @brief Destructeur virtuel
        */
        virtual ~State() = default;

        /**
        * @brief Appelé lorsque le State devient actif
        */
        virtual void onEnter();

        /**
        * @brief Appelé lorsque le State quitte la pile active
        */
        virtual void onExit();

        /**
        * @brief Mise à jour logique du State
        * @param dt Delta time en secondes
        */
        virtual void update(float dt) = 0;

        /**
        * @brief Rendu du State
        * @param window Fenêtre SFML
        */
        virtual void render(sf::RenderWindow& window) = 0;

        /**
        * @brief Gestion des événements
        * @param event Événement SFML
        */
        virtual void handleEvent(const sf::Event& event) = 0;

        /**
        * @brief Indique si le State bloque ceux en dessous
        *
        * @return true si le rendu/mise à jour doit être exclusive
        */
        virtual bool isBlocking() const { return true; }

    protected:
        CoreEngine& m_core; /**< Accès aux systèmes centraux */
    };
}

#endif // _CORE_STATE_HPP__