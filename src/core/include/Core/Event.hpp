#ifndef _CORE_EVENT_HPP__
#define _CORE_EVENT_HPP__

#include <string>

namespace Core
{
    /**
    * @brief Classe de base optionnelle pour les événements.
    *
    * Dans PokeMaker, les événements peuvent être de simples structs.
    * Cette classe sert principalement de point commun documentaire
    * et peut être étendue si des métadonnées globales sont nécessaires.
    *
    * Exemples d'usage :
    * - événements d'éditeur (sélection, modification)
    * - événements gameplay (interaction, trigger)
    */
    struct Event
    {
        /**
        * @brief Nom lisible de l'événement (debug / logs)
        */
        std::string name;

        /**
        * @brief Constructeur
        */
        explicit Event(const std::string& eventName = "")
        : name(eventName)
        {
        }

        /**
        * @brief Destructeur virtuel
        */
        virtual ~Event() = default;
    };
}

#endif // _CORE_EVENT_HPP__