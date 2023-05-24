#include "Engine.h"

Engine* Engine::EngineInstance = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG) != 0)
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	IsEngineRunning = true;
	return true;
}

void Engine::Run()
{
	Init();
	EngineMainApplication = new MainApplication("Engine Template");
	EventHandler* eventHandler = new EventHandler();
	
	while (IsEngineRunning)
	{
		eventHandler->Listen();
		Update();
	}
}

void Engine::Update()
{
	EngineMainApplication->ClearBackground();
}

void Engine::Quit()
{
	if (EngineMainApplication != nullptr) EngineMainApplication->DestroyApplication();
	IsEngineRunning = false;
}
