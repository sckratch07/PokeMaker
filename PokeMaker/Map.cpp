#include "Map.h"

int tileSize[2] = { 16, 16 };
int tileMap[2] = { 10, 10 };
bool gridVisibility = true;
float gridColor[4] = { 1.f, 1.f, 1.f, 1.f };

void updateMap(sf::Vector2u viewSize)
{
	if (ImGui::BeginChild("Tiles", { 0, 0 }, ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY,
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Text("TileMap Size : ");
		ImGui::InputInt2("##tileMapSize", tileMap, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsDecimal);
		ImGui::Text("Tile Size : ");
		ImGui::InputInt2("##tileSize", tileSize, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsDecimal);
		ImGui::Text("Grid Visibility : ");
		ImGui::Checkbox("##gridVisibility", &gridVisibility);
		if (gridVisibility)
		{
			ImGui::Text("Grid Color : ");
			ImGui::ColorEdit4("##gridColor", gridColor, ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB );
		}
	}
	ImGui::EndChild();
}

void renderGril(sf::RenderWindow& window)
{
	if (!gridVisibility) return;

    sf::VertexArray lines(sf::PrimitiveType::Lines);

    for (int x = 0; x <= tileMap[0] * tileSize[0]; x += tileSize[0]) {
        lines.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2f(x, tileMap[1] * tileSize[1]), sf::Color::White));
    }

    for (int y = 0; y <= tileMap[1] * tileSize[1]; y += tileSize[1]) {
        lines.append(sf::Vertex(sf::Vector2f(0, y), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2f(tileMap[0] * tileSize[0], y), sf::Color::White));
    }

    window.draw(lines);
}
