#include "JsonUtils.hpp"
#include <fstream>

json JsonUtils::loadJSON(std::string filePath)
{
	json data;
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> data;
		file.close();
	}

	return data;
}

void JsonUtils::saveJSON(std::string filePath, json data)
{
	std::ofstream file(filePath);
	if (file.is_open())
	{
		file << data.dump(4);
		file.close();
	}
}