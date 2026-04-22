#include "GameStateMachine.h"
#include "Engine.h"
#include "LevelManager.h"

GameStateMachine::GameStateMachine(Engine& engine, LevelManager& levelManager, ViewRenderer& viewRenderer, TemplateGameplayRules& rules)
    : mEngine(engine), mLevelManager(levelManager), mViewRenderer(viewRenderer), mRules(rules) {}

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
        mViewRenderer.Render();
        if (mLevelManager.IsCurrentComplete())
            mRules.SetCurrentGameState(NewLevel);
        break;
    }
    case LifeLost:
    {
        if (mViewRenderer.DisplayModalMessage(SDL_SCANCODE_SPACE, "Life Lost! Press space key", 250, 520))
            mRules.SetCurrentGameState(Running);
        break;
    }
    case GameOver:
    {
        if (mViewRenderer.DisplayModalMessage(SDL_SCANCODE_SPACE, "Game Over!", 310, 520))
            mRules.SetCurrentGameState(Restarting);
        break;
    }
    case NewLevel:
    {
        mEngine.Update(delta);
        mViewRenderer.ResetViewport();
        if (mViewRenderer.DisplayModalMessage(SDL_SCANCODE_SPACE, "New Level Unlocked!", 250, 520))
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
        mViewRenderer.ResetViewport();
        mViewRenderer.DisplayModalMessage(SDL_SCANCODE_SPACE, "You beat it!", 310, 520);
        break;
    }
    }
}
