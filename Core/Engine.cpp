#include "Engine.h"

#include "..\Entities\Brick.h"
#include "..\Core\Ticker.h"

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG) != 0)
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
	EngineMainApplication = make_unique<MainApplication>("Engine Template");
	EngineTextPrinter = make_unique<TextPrinter>(GetRenderer());
	SetupLevels();
	GameplayRules->SetCurrentGameState(Running);
	return true;
}

void Engine::SetupLevels()
{
	mLevelManager = make_unique<LevelManager>();
	mLevelManager->LoadCurrent();
}

void Engine::Run()
{
	EventHandler& MainEventHandler = EventHandler::GetInstance();
	GameplayRules = make_unique<TemplateGameplayRules>(TemplateGameplayRules(525));
	while (IsEngineRunning)
	{
		Ticker::GetInstance().Tick();
		float delta = Ticker::GetInstance().GetDeltaTime();
		MainEventHandler.Listen();
		switch (GameplayRules->GetCurrentGameState())
		{
		case Initializing:
		{
			Init();			
			break;
		}

		case Running:
		{	
			Update(delta);
			Render();
			if (mLevelManager->GetCurrentLevel().IsComplete())
			{
				GameplayRules->SetCurrentGameState(NewLevel);
			}
			break;
		}
		
		case LifeLost:
		{
			if (DisplayModalMessage(SDL_SCANCODE_SPACE, "Life Lost! Press space key", 250, 520))
			{
				GameplayRules->SetCurrentGameState(Running);
			}
			break;
		}
		case GameOver:
		{
			if (DisplayModalMessage(SDL_SCANCODE_SPACE, "Game Over!", 310, 520))
			{
				GameplayRules->SetCurrentGameState(Restarting);
			}
			break;
		}
		case NewLevel:
		{			
			Update(delta);
			ResetViewport();
			if (DisplayModalMessage(SDL_SCANCODE_SPACE, "New Level Unlocked!", 250, 520))
			{
				if (mLevelManager->AdvanceLevel())
				{
					GameplayRules->SetCurrentGameState(Running);
				}
				else
				{
					GameplayRules->SetCurrentGameState(GameComplete);
				}
			}
			break;			
		}
		case Restarting:
		{
			mLevelManager->Restart();
			GameplayRules->SetHealth(3);
			GameplayRules->SetCurrentGameState(Running);
			break;
		}
		case GameComplete:
		{
			ResetViewport();
			DisplayModalMessage(SDL_SCANCODE_SPACE, "You beat it!", 310, 520);
			break;
		}
		}
	}
}

void Engine::Update(float delta)
{
	mLevelManager->GetCurrentLevel().Update(delta);
}

void Engine::Render()
{
	ResetViewport();
	mLevelManager->GetCurrentLevel().Render();
	SDL_RenderPresent(GetRenderer());
}

void Engine::ResetViewport()
{
	SDL_SetRenderDrawColor(GetRenderer(), 35, 35, 35, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(GetRenderer());
}

void Engine::Quit()
{
	if (EngineMainApplication != nullptr) EngineMainApplication->DestroyApplication();
	IsEngineRunning = false;
}

bool Engine::DisplayModalMessage(SDL_Scancode keyCode, string message, int x, int y)
{
	if (EventHandler::GetInstance().GetKeyDown(keyCode) == 1)
	{
		return true;
	}
	EngineTextPrinter->PrintText(message, x, y);
	SDL_RenderPresent(GetRenderer());
	return false;
}
