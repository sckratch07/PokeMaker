#ifndef _CORE_EVENTMANAGER_HPP__
#define _CORE_EVENTMANAGER_HPP__

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>

namespace Core
{
    /**
     * @brief Gestionnaire d'événements générique et découplé.
     *
     * L'EventManager permet la communication entre systèmes, States
     * et modules sans dépendances directes.
     *
     * Il est particulièrement utile pour :
     * - interactions NPC / joueur
     * - événements d'éditeur (sélection, modification)
     * - signaux globaux (changement de map, sauvegarde)
     */
    class EventManager
    {
    public:
        /**
        * @brief S'abonner à un type d'événement
         * @tparam EventType Type de l'événement
         * @param callback Fonction appelée lors de l'événement
         */
        template<typename EventType>
        void subscribe(std::function<void(const EventType&)> callback)
        {
            auto& listeners = m_listeners[typeid(EventType)];
            listeners.push_back([callback](const void* event)
                {
                    callback(*static_cast<const EventType*>(event));
                }
            );
        }
        
        /**
         * @brief Émettre un événement
         * @tparam EventType Type de l'événement
         * @param event Instance de l'événement
         */
        template<typename EventType>
        void emit(const EventType& event)
        {
            auto it = m_listeners.find(typeid(EventType));
            if (it == m_listeners.end())
                return;
            
            for (auto& listener : it->second)
            {
                listener(&event);
            }
        }
        
        /**
         * @brief Supprime tous les abonnements
         */
        void clear()
        {
            m_listeners.clear();
        }
        
    private:
        using Listener = std::function<void(const void*)>;
        std::unordered_map<std::type_index, std::vector<Listener>> m_listeners;
    };
}

#endif // _CORE_EVENTMANAGER_HPP__