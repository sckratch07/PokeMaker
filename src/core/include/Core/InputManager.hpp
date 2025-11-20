#ifndef _CORE_INPUTMANAGER_HPP__
#define _CORE_INPUTMANAGER_HPP__

#include <unordered_map>
#include <mutex>

/**
 * @file InputManager.hpp
 * @brief Gestion basique des états d'entrées (clefs / boutons).
 *
 * Note : Core ne dépend pas d'une bibliothèque d'entrées spécifique.
 *       Les modules supérieurs (ex: Engine avec SFML) doivent appeler
 *       setKeyState / setMouseButtonState quand des événements surviennent.
 */

namespace Core
{
/**
 * @brief Gestionnaire d'état d'entrée minimal et thread-safe.
 *
 * Les touches et boutons sont identifiées par des entiers (codes).
 * L'implémetation concrète (mapping des codes) est dans la couche
 * de plateforme (Engine/Renderer).
 */
class InputManager
{
public:
    InputManager() = default;
    ~InputManager() = default;

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    /**
     * @brief Met à jour l'état d'une touche/bouton.
     * @param code Code entier identifiant la touche/bouton.
     * @param down true si appuyé, false sinon.
     */
    void setKeyState(int code, bool down);

    /**
     * @brief Retourne l'état actuel d'une touche.
     */
    bool isKeyDown(int code) const;

    /**
     * @brief Efface tous les états (utile entre scènes).
     */
    void clear();

private:
    mutable std::mutex m_mutex;
    std::unordered_map<int, bool> m_keyStates;
};

} // namespace Core

#endif
