#ifndef _EDITOR_WFCGENERATOR_HPP__
#define _EDITOR_WFCGENERATOR_HPP__

/**
 * @file WFCGenerator.hpp
 * @brief Générateur procédural basé sur Wave Function Collapse (WFC).
 *
 * Permet de générer une map de tuiles avec règles et poids configurables.
 */

#include <vector>
#include <unordered_map>
#include <string>
#include <optional>
#include <random>

namespace Editor {

/**
 * @struct TileRule
 * @brief Règles de compatibilité d'une tuile avec ses voisines.
 */
struct TileRule {
    int id; ///< identifiant de la tuile
    std::unordered_map<std::string, std::vector<int>> neighbors; ///< voisins autorisés : "up", "down", "left", "right"
    float weight = 1.0f; ///< poids pour la sélection aléatoire
};

/**
 * @class WFCGenerator
 * @brief Générateur procédural WFC avec règles et poids.
 */
class WFCGenerator
{
public:
    WFCGenerator();
    ~WFCGenerator();

    /**
     * @brief Définit la seed du générateur.
     * @param seed Valeur de la seed. Si non fournie, le générateur sera aléatoire.
     */
    void setSeed(std::optional<unsigned int> seed);

    /**
     * @brief Ajoute une règle pour une tuile.
     * @param rule La règle à ajouter.
     */
    void addRule(const TileRule& rule);

    /**
     * @brief Génère une map procédurale.
     * @param width Largeur en tuiles.
     * @param height Hauteur en tuiles.
     * @return vecteur 2D de tuiles (width*height) rempli selon les règles.
     */
    std::vector<int> generate(int width, int height);

private:
    std::vector<TileRule> m_rules;
    std::unordered_map<int, TileRule> m_ruleMap;
    std::mt19937 m_rng;
    bool m_seedSet;
};

} // namespace Editor

#endif
