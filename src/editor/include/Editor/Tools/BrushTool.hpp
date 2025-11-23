#ifndef _EDITOR_BRUSHTOOL_HPP__
#define _EDITOR_BRUSHTOOL_HPP__

#include "Editor/EditorTool.hpp"
#include <SFML/Graphics.hpp>

namespace Editor {

class BrushTool : public EditorTool
{
public:
    BrushTool() = default;
    ~BrushTool() override = default;

    void begin() override {}
    void update() override {}
    void end() override {}

    const char* name() const override { return "Pinceau"; }
    EditorToolType type() const override { return EditorToolType::Brush; }
};

} // namespace Editor

#endif
