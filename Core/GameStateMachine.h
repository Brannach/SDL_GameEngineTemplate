#pragma once
#include "Gameplay.h"

class Engine;
class LevelManager;
class ViewRenderer;

class GameStateMachine
{
public:
    GameStateMachine(Engine& engine, LevelManager& levelManager,
                 ViewRenderer& viewRenderer, TemplateGameplayRules& rules);
    void Update(float delta);

private:
    Engine& mEngine;
    LevelManager& mLevelManager;
    TemplateGameplayRules& mRules;
    ViewRenderer& mViewRenderer;
};
