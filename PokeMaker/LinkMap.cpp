#include "LinkMap.hpp"

LinkMap::LinkMap() : enterMap("\0"), exitMap("\0"), enterPos(0,0), exitPos(0,0), actionDistance(0.f) {}

json LinkMap::Serialize() const
{
    json j;
    j["enterMap"] = enterMap;
    j["exitMap"] = exitMap;
    j["enterPosX"] = enterPos.x;
    j["enterPosY"] = enterPos.y;
    j["exitPosX"] = exitPos.x;
    j["exitPosY"] = exitPos.y;
    j["range"] = actionDistance;
    
    return j;
}

void LinkMap::Deserialize(const json& jsonData)
{
    enterMap = jsonData.value("enterMap", "");
    exitMap = jsonData.value("exitMap", "");
    enterPos.x = jsonData.value("enterPosX", 0);
    enterPos.y = jsonData.value("enterPosY", 0);
    exitPos.x = jsonData.value("exitPosX", 0);
    exitPos.y = jsonData.value("exitPosY", 0);
    actionDistance = jsonData.value("exitPosY", 0.f);
}
