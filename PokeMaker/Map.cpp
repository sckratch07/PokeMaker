#include "Map.h"

int tileSize[2] = { 16, 16 };
int tileMap[2] = { 64, 64 };

void updateMap()
{
	if (ImGui::BeginChild("Tiles", { 0, 0 }, ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY,
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Text("TileMap Size : ");
		ImGui::InputInt2("##", tileMap, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsDecimal);
		ImGui::Text("Tile Size : ");
		ImGui::InputInt2("##", tileSize, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsDecimal);
		ImGui::EndChild();
	}
}

void renderMap(sf::RenderWindow& window)
{
	sf::VertexArray lines(sf::PrimitiveType::Lines); 
}
