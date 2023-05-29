#include "Engine.h"
#include "BouncingBall.h"
#include "Brick.h"
#include "Paddle.h"

Engine* Engine::EngineInstance = nullptr;

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

void Engine::LoadScene()
{
	TextureRenderer::GetInstance()->Load("ball", "resources/actors/ball_marble.png", GetRenderer());
	TextureRenderer::GetInstance()->Load("paddle", "resources/actors/paddle.png", GetRenderer());
	BouncingBall* Ball = new BouncingBall(new Properties("ball", 400, 300, 24, 24, SDL_FLIP_NONE));
	Paddle* paddle = new Paddle(new Properties("paddle", 350, 500, 100, 40, SDL_FLIP_NONE));
	RenderActor.push_back(Ball);
	RenderActor.push_back(paddle);

	if (!MapParser::GetInstance()->Load())
		cout << "Failed to load map" << endl;
	else
	{
		CurrentGameMap = MapParser::GetInstance()->GetMap("Map01");
		CurrentGameMap->Render();
	}
}
void Engine::Run()
{
	Init();
	LoadScene();
	while (IsEngineRunning)
	{
		EventHandler::GetInstance()->Listen();
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
