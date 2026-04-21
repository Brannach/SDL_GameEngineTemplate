#pragma once
#include "ILevel.h"
#include "../Map/GameMap.h"
#include <string>
#include <list>
#include <memory>

class BreakoutLevel : public ILevel
{
public:
    BreakoutLevel(std::string mapId, std::string mapFile);

    void Load() override;
    void Unload() override;
    void Update(float delta) override;
    void Render() override;
    bool IsComplete() override;
    const std::list<std::unique_ptr<Actor>>& GetActors() override;

    void AddActor(std::unique_ptr<Actor> actor);
    void RemoveActor(Actor* actor);

private:
    std::string mMapId;
    std::string mMapFile;
    std::unique_ptr<GameMap> mMap;
    std::list<std::unique_ptr<Actor>> mActors;
};