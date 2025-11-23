#ifndef _EDITOR_EDITORTOOL_HPP__
#define _EDITOR_EDITORTOOL_HPP__

namespace Editor {

/**
 * @enum EditorToolType
 * @brief Représente les types d’outils disponibles dans l’éditeur.
 */
enum class EditorToolType {
    Selection,
    Brush,
    Fill
};

class EditorTool
{
public:
    virtual ~EditorTool() = default;

    virtual void begin() = 0;
    virtual void update() = 0;
    virtual void end() = 0;

    /** @brief Nom affichable */
    virtual const char* name() const = 0;

    /** @brief Type d’outil (permet la gestion par EditorApplication) */
    virtual EditorToolType type() const = 0;
};

} // namespace Editor

#endif
