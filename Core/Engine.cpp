#include "Engine.h"

#include <SDL_image.h>

#include "EventHandler.h"
#include "..\Entities\Brick.h"
#include "..\Core\Ticker.h"
#include "GameStateMachine.h"

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG) != 0)
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
	EngineMainApplication = make_unique<MainApplication>("Engine Template");
	SetupLevels();
	mViewRenderer = make_unique<ViewRenderer>(GetRenderer(), *mLevelManager);
	
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
	Init();
	GameStateMachine stateMachine(*this, *mLevelManager, *mViewRenderer, *GameplayRules);
	while (IsEngineRunning)
	{
		Ticker::GetInstance().Tick();
		float delta = Ticker::GetInstance().GetDeltaTime();
		MainEventHandler.Listen();
		stateMachine.Update(delta);
	}
}

void Engine::Update(float delta)
{
	mLevelManager->GetCurrentLevel().Update(delta);
}

void Engine::Quit()
{
	if (EngineMainApplication != nullptr) EngineMainApplication->DestroyApplication();
	IsEngineRunning = false;
}
