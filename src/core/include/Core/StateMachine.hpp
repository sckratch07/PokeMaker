#ifndef _CORE_STATEMACHINE_HPP__
#define _CORE_STATEMACHINE_HPP__

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>

namespace Core
{
    class State;

    /**
    * @brief Gère la pile de States actifs.
    *
    * La StateMachine est responsable de :
    * - L'ajout, le retrait et le remplacement de States
    * - L'appel des callbacks onEnter / onExit
    * - La propagation des mises à jour, rendus et événements
    *
    * Elle fonctionne comme une pile (stack) :
    * - Le State au sommet est toujours actif
    * - Les States en dessous peuvent être bloqués ou non
    */
    class StateMachine
    {
    public:
        /**
        * @brief Constructeur par défaut
        */
        StateMachine() = default;

        /**
        * @brief Destructeur
        *
        * Appelle onExit sur tous les States restants.
        */
        ~StateMachine();

        /**
        * @brief Ajoute un State au sommet de la pile
        * @param state State à ajouter
        */
        void pushState(std::unique_ptr<State> state);

        /**
        * @brief Retire le State actif
        */
        void popState();

        /**
        * @brief Remplace le State actif par un autre
        * @param state Nouveau State
        */
        void replaceState(std::unique_ptr<State> state);

        /**
        * @brief Supprime tous les States
        */
        void clear();

        /**
        * @brief Met à jour les States actifs
        * @param dt Delta time
        */
        void update(float dt);

        /**
        * @brief Rendu des States actifs
        * @param window Fenêtre SFML
        */
        void render(sf::RenderWindow& window);

        /**
        * @brief Propage les événements
        * @param event Événement SFML
        */
        void handleEvent(const sf::Event& event);

        /**
        * @brief Vérifie si la pile est vide
        */
        bool empty() const { return m_states.empty(); }

    private:
        std::vector<std::unique_ptr<State>> m_states; /**< Pile de States */
    };
}


#endif // _CORE_STATEMACHINE_HPP__