#ifndef _EDITOR_NPCEDITOR_HPP__
#define _EDITOR_NPCEDITOR_HPP__

/**
 * @file NPCEditor.hpp
 * @brief Outils pour éditer les PNJ (position, sprite, comportement).
 *
 * Simple UI permettant de lister / ajouter / modifier des PNJ.
 */

#include <vector>
#include <string>

namespace Editor {

/**
 * @struct NPCData
 * @brief Représentation simple d'un PNJ (placeholder).
 */
struct NPCData {
    std::string name;
    int x = 0;
    int y = 0;
    int level = 1;
};

/**
 * @class NPCEditor
 * @brief Editeur basique de PNJ.
 */
class NPCEditor
{
public:
    NPCEditor();
    ~NPCEditor();

    void render();

    void addNPC(const NPCData& npc);

private:
    std::vector<NPCData> m_npcs;
    int m_selected;
};

} // namespace Editor

#endif
