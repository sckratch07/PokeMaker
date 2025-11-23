#ifndef _EDITOR_SELECTIONTOOL_HPP__
#define _EDITOR_SELECTIONTOOL_HPP__

#include "Editor/EditorTool.hpp"
#include <SFML/Graphics.hpp>

namespace Editor {

class SelectionTool : public EditorTool
{
public:
    SelectionTool() = default;
    ~SelectionTool() override = default;

    void begin() override {}
    void update() override {}
    void end() override {}

    const char* name() const override { return "Selection"; }
    EditorToolType type() const override { return EditorToolType::Selection; }
};

} // namespace Editor

#endif
