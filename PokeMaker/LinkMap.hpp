#pragma once
#include "SFML/Graphics.hpp"
#include "nlohmann/json.hpp"
#include <string>

using json = nlohmann::json;

class LinkMap
{
public:
	LinkMap();
	LinkMap(std::string enterMap, std::string& exitMap, sf::Vector2i enterPos, sf::Vector2i exitPos, float actionDistance)
		: enterMap(enterMap), exitMap(exitMap), enterPos(enterPos), exitPos(exitPos), actionDistance(actionDistance) {};

    json Serialize() const;
	void Deserialize(const json& jsonData);

	const std::string& GetEnterMap() const { return enterMap; }
	const std::string& GetExitMap() const { return exitMap; }
	const sf::Vector2i& GetEnterPos() const { return enterPos; }
	const sf::Vector2i& GetExitPos() const { return exitPos; }
	const float& GetActionRange() const { return actionDistance; }

private:
	std::string enterMap;
	std::string exitMap;

	sf::Vector2i enterPos;
	sf::Vector2i exitPos;

	float actionDistance;
};

