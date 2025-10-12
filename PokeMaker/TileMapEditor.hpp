#pragma once
#include "TileMap.hpp"

class TileMapEditor
{
	void paintTile();
	void selectTile();
	void loadTilesetPreview(std::string path);
private:
	int selectedTile;
	std::string activeLayer;
};
