#include "Engine.h"
#include "BouncingBall.h"

Engine* Engine::EngineInstance = nullptr;
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
	TextureRenderer::GetInstance()->Load("ball", "resources/actors/ball_marble.png", GetRenderer());
	BouncingBall* Ball = new BouncingBall(new Properties("ball", 400, 300, 24, 24, SDL_FLIP_NONE));
	RenderActor.push_back(Ball);
	while (IsEngineRunning)
	{
		eventHandler->Listen();
		Update();
		Render();
	}
}

void Engine::Update()
{
	for (Actor* anActor : RenderActor)
	{
		anActor->Update(1);
	}
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(GetRenderer(), 35, 35, 35, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(GetRenderer());
	for (Actor* anActor : RenderActor)
	{
		anActor->Draw();
	}
	SDL_RenderPresent(GetRenderer());
}

void Engine::Quit()
{
	if (EngineMainApplication != nullptr) EngineMainApplication->DestroyApplication();
	IsEngineRunning = false;
}
