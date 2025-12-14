#ifndef _CORE_TIMER_HPP__
#define _CORE_TIMER_HPP__

#include <chrono>

namespace Core
{
    /**
    * @brief Gestionnaire de temps et utilitaires de mesure.
    *
    * La classe Timer fournit :
    * - le calcul du delta time
    * - des chronomètres simples
    * - une base commune pour animations et interpolations
    *
    * Utilisée par :
    * - boucle principale
    * - animations de tiles / sprites
    * - systèmes nécessitant le temps
    */
    class Timer
    {
    public:
        /**
        * @brief Constructeur
        */
        Timer();

        /**
        * @brief Met à jour le timer
        *
        * Doit être appelé une fois par frame.
        */
        void tick();

        /**
        * @brief Retourne le delta time en secondes
        */
        float deltaTime() const;

        /**
        * @brief Retourne le temps écoulé depuis le démarrage
        */
        float elapsedTime() const;

        /**
        * @brief Réinitialise le timer
        */
        void reset();

    private:
        using clock = std::chrono::high_resolution_clock;

        clock::time_point m_start; /**< Temps de démarrage */
        clock::time_point m_last; /**< Dernière frame */
        float m_deltaTime = 0.f; /**< Delta time en secondes */
    };
}

#endif // _CORE_TIMER_HPP__