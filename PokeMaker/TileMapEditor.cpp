//#include "Map.h"
//
//inline sf::Color floatToColor(float col[4])
//{
//	return sf::Color(
//		(uint8_t)(col[0] * 255.f),	// Red
//		(uint8_t)(col[1] * 255.f),	// Green
//		(uint8_t)(col[2] * 255.f),	// Blue
//		(uint8_t)(col[3] * 255.f));	// Alpha
//}
//
//inline void updateGril(sf::VertexArray& vArray, int tileMapSize[2], int tileSize[2], sf::Color color)
//{
//	vArray.clear();
//
//	sf::Vector2f offset(tileMapSize[0] * tileSize[0] * -0.5f, tileMapSize[1] * tileSize[1] * -0.5f);
//
//	for (float x = 0; x <= tileMapSize[0] * tileSize[0]; x += tileSize[0]) {
//		vArray.append(sf::Vertex(sf::Vector2f(x, 0) + offset, color));
//		vArray.append(sf::Vertex(sf::Vector2f(x, (float)(tileMapSize[1] * tileSize[1])) + offset, color));
//	}
//
//	for (float y = 0; y <= tileMapSize[1] * tileSize[1]; y += tileSize[1]) {
//		vArray.append(sf::Vertex(sf::Vector2f(0, y) + offset, color));
//		vArray.append(sf::Vertex(sf::Vector2f((float)(tileMapSize[0] * tileSize[0]), y) + offset, color));
//	}
//}
//
//void MapWidget::onInit()
//{
//	this->lines = sf::VertexArray(sf::PrimitiveType::Lines);
//	updateGril(this->lines, this->tileMapSize, this->tileSize, floatToColor(this->gridColor));
//}
//
//void MapWidget::onUpdate(sf::RenderWindow& window, float dt)
//{
//	if (ImGui::BeginChild("Tiles", { 0, 0 }, ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY,
//		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
//	{
//		ImGui::Text("TileMap Size : ");
//		if (ImGui::InputInt2("##tileMapSize", tileMapSize, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsDecimal))
//			updateGril(this->lines, this->tileMapSize, this->tileSize, floatToColor(this->gridColor));
//
//		ImGui::Text("Tile Size : ");
//		if (ImGui::InputInt2("##tileSize", tileSize, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsDecimal))
//			updateGril(this->lines, this->tileMapSize, this->tileSize, floatToColor(this->gridColor));
//
//		ImGui::Text("Grid Visibility : ");
//		ImGui::Checkbox("##gridVisibility", &gridVisibility);
//		if (gridVisibility)
//		{
//			ImGui::Text("Grid Color : ");
//			ImGui::ColorEdit4("##gridColor", gridColor, ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB);
//		}
//	}
//	ImGui::EndChild();
//}
//
//void MapWidget::onDraw(sf::RenderWindow& window)
//{
//	if (!this->gridVisibility) return;
//	window.draw(this->lines);
//}
//
//void MapWidget::onDestroy()
//{
//	this->lines.clear();
//}
