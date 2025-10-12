#pragma once
#include "TileMapEditor.hpp"
#include "EntityEditor.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui-SFML.h"

class EditorUI
{
public:
	void drawProjectPanel();
	void drawTileMapEditor();
	void drawEntityEditor();
private:
	TileMapEditor mapEditor;
	bool showTileMapEditor;

	EntityEditor entityEditor;
	bool showEntityEditor;
};

