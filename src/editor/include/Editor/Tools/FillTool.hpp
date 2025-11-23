#ifndef _EDITOR_FILLTOOL_HPP__
#define _EDITOR_FILLTOOL_HPP__

#include "Editor/EditorTool.hpp"
#include <SFML/Graphics.hpp>

namespace Editor {

class FillTool : public EditorTool
{
public:
    FillTool() = default;
    ~FillTool() override = default;

    void begin() override {}
    void update() override {}
    void end() override {}

    const char* name() const override { return "Remplissage"; }
    EditorToolType type() const override { return EditorToolType::Fill; }
};

} // namespace Editor

#endif
