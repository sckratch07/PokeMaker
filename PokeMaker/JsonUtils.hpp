#pragma once
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace JsonUtils
{
	json loadJSON(std::string file);
	void saveJSON(std::string file, json data);
}

