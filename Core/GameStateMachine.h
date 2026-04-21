#pragma once
#include "Gameplay.h"

class Engine;
class LevelManager;

class GameStateMachine
{
public:
    GameStateMachine(Engine& engine, LevelManager& levelManager, TemplateGameplayRules& rules);
    void Update(float delta);

private:
    Engine& mEngine;
    LevelManager& mLevelManager;
    TemplateGameplayRules& mRules;
};
