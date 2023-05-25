#include "Engine.h"
#include "BouncingBall.h"

Engine* Engine::EngineInstance = nullptr;
BouncingBall* Ball;
MainApplication* Engine::EngineMainApplication = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG) != 0)
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
	EngineMainApplication = new MainApplication("Engine Template");
	IsEngineRunning = true;
	return true;
}

void Engine::Run()
{
	Init();
	EventHandler* eventHandler = new EventHandler();
	TextureRenderer::GetInstance()->Load("ball", "resources/actors/ball_marble.png", EngineMainApplication->MainWindowRenderer);
	Ball = new BouncingBall(new Properties("ball", 400, 300, 32, 32, SDL_FLIP_NONE));
	while (IsEngineRunning)
	{
		eventHandler->Listen();
		Update();
	}
}

void Engine::Update()
{
	SDL_SetRenderDrawColor(EngineMainApplication->MainWindowRenderer, 35, 35, 35, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(EngineMainApplication->MainWindowRenderer);
	Ball->Draw();
	SDL_RenderPresent(EngineMainApplication->MainWindowRenderer);
}

void Engine::Quit()
{
	if (EngineMainApplication != nullptr) EngineMainApplication->DestroyApplication();
	IsEngineRunning = false;
}
