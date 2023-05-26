#include "Engine.h"
#include "BouncingBall.h"
#include "Brick.h"

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
	Brick* brick = new Brick(new Properties("", 0, 0, 45, 25, SDL_FLIP_NONE), { 150, 55, 66, 255 });
	Brick* brick2 = new Brick(new Properties("", 45, 0, 45, 25, SDL_FLIP_NONE), { 50, 155, 66, 255 });
	RenderActor.push_back(brick);
	RenderActor.push_back(brick2);
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
