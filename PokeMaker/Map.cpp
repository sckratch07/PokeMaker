#include "Map.h"

int tileSize[2] = {16, 16};

void updateMap()
{
	if (ImGui::BeginChild("Tiles", { 0,0 }, ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY,
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::InputInt2("Tile Size", tileSize, ImGuiInputTextFlags_AutoSelectAll);
		ImGui::EndChild();
	}
}
