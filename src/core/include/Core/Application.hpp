#ifndef _CORE_APPLICATION_HPP__
#define _CORE_APPLICATION_HPP__

#include <functional>
#include <chrono>
#include <atomic>

namespace Core
{
/**
 * @brief Classe Application générique gérant la boucle principale.
 *
 * Cette classe ne sait rien du rendu ni des entrées spécifiques (SFML/SDL).
 * Elle fournit un mécanisme simple pour : initialiser, démarrer / arrêter la
 * boucle principale, et définir des callbacks d'update / render.
 *
 * Exemple d'utilisation :
 * @code
 * Core::Application app;
 * app.setUpdateCallback([](double dt){ logique });
 * app.setRenderCallback([](double dt){ rendu });
 * app.run();
 * @endcode
 */
class Application
{
public:
    using Clock = std::chrono::steady_clock;
    using Duration = std::chrono::duration<double>;

    Application() = default;
    ~Application() = default;

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    /**
     * @brief Définit la fonction appelée à chaque update (logique).
     * @param cb Fonction prenant en paramètre le delta-time en secondes.
     */
    void setUpdateCallback(std::function<void(double)> cb);

    /**
     * @brief Définit la fonction appelée à chaque frame pour le rendu.
     * @param cb Fonction prenant en paramètre le delta-time en secondes.
     */
    void setRenderCallback(std::function<void(double)> cb);

    /**
     * @brief Démarre la boucle principale (bloquante).
     * @note Retourne lorsque stop() est appelé.
     */
    void run();

    /**
     * @brief Arrête la boucle principale.
     */
    void stop();

    /**
     * @brief Définit une mise à jour avec timestep fixe.
     * Si timestep <= 0, la boucle utilisera un timestep variable (dt réel).
     * @param timestep secondes (ex: 1.0 / 60.0)
     */
    void setFixedTimestep(double timestep);

    /**
     * @brief Retourne vrai si l'application est en cours d'exécution.
     */
    bool isRunning() const noexcept;

private:
    std::function<void(double)> m_updateCallback = nullptr;
    std::function<void(double)> m_renderCallback = nullptr;

    std::atomic<bool> m_running { false };
    double m_fixedTimestep = 0.0;
};

} // namespace Core

#endif
