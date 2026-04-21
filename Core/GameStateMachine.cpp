#include "GameStateMachine.h"
#include "Engine.h"
#include "LevelManager.h"

GameStateMachine::GameStateMachine(Engine& engine, LevelManager& levelManager, TemplateGameplayRules& rules)
    : mEngine(engine), mLevelManager(levelManager), mRules(rules) {}

void GameStateMachine::Update(float delta)
{
    switch (mRules.GetCurrentGameState())
    {
    case Initializing:
    {
        mEngine.Init();
        break;
    }
    case Running:
    {
        mEngine.Update(delta);
        mEngine.Render();
        if (mLevelManager.IsCurrentComplete())
            mRules.SetCurrentGameState(NewLevel);
        break;
    }
    case LifeLost:
    {
        if (mEngine.DisplayModalMessage(SDL_SCANCODE_SPACE, "Life Lost! Press space key", 250, 520))
            mRules.SetCurrentGameState(Running);
        break;
    }
    case GameOver:
    {
        if (mEngine.DisplayModalMessage(SDL_SCANCODE_SPACE, "Game Over!", 310, 520))
            mRules.SetCurrentGameState(Restarting);
        break;
    }
    case NewLevel:
    {
        mEngine.Update(delta);
        mEngine.ResetViewport();
        if (mEngine.DisplayModalMessage(SDL_SCANCODE_SPACE, "New Level Unlocked!", 250, 520))
        {
            if (mLevelManager.AdvanceLevel())
                mRules.SetCurrentGameState(Running);
            else
                mRules.SetCurrentGameState(GameComplete);
        }
        break;
    }
    case Restarting:
    {
        mLevelManager.Restart();
        mRules.SetHealth(3);
        mRules.SetCurrentGameState(Running);
        break;
    }
    case GameComplete:
    {
        mEngine.ResetViewport();
        mEngine.DisplayModalMessage(SDL_SCANCODE_SPACE, "You beat it!", 310, 520);
        break;
    }
    }
}
