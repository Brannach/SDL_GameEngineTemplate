#include "Engine.h"
#include "BouncingBall.h"
#include "Brick.h"
#include "Paddle.h"
#include "Health.h"

Engine* Engine::EngineInstance = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG) != 0)
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
	EngineMainApplication = new MainApplication("Engine Template");
	

	GameplayRules->SetCurrentGameState(Running);
	return true;
}

void Engine::LoadScene()
{
	TextureRenderer::GetInstance()->Load("ball", "resources/actors/ball_marble.png", GetRenderer());
	TextureRenderer::GetInstance()->Load("paddle", "resources/actors/paddle.png", GetRenderer());
	TextureRenderer::GetInstance()->Load("health", "resources/actors/health.png", GetRenderer());
	BouncingBall* Ball = new BouncingBall(new Properties("ball", 400, 300, 24, 24));
	Paddle* GamePaddle = new Paddle(new Properties("paddle", 350, 500, 100, 25));
	Health* PlayerHealth = new Health(new Properties("health", 700, 550, 20, 20));

	RenderActor.push_back(Ball);
	RenderActor.push_back(GamePaddle);
	RenderActor.push_back(PlayerHealth);

	CurrentGameMap = MapParser::GetInstance()->Load("Map01", "Resources/Maps/Map01.tmx");
	if (CurrentGameMap == nullptr)
	{
		cout << "Failed to load map" << endl;
	}
	else
	{
		CurrentGameMap->Render();
	}
}

void Engine::Run()
{
	EventHandler* eventHandler = EventHandler::GetInstance();
	GameplayRules = new TemplateGameplayRules(512);
	while (IsEngineRunning)
	{
		switch (GameplayRules->GetCurrentGameState())
		{
		case Initializing:
		{
			Init();
			LoadScene();
			break;
		}

		case Running:
		{
			eventHandler->Listen();
			GameplayRules->Update();
			Update();
			Render();
			break;
		}
		
		case LifeLost:
		{
			eventHandler->Listen();
			if (eventHandler->GetKeyDown(SDL_SCANCODE_SPACE) == 1)
			{
				GameplayRules->SetCurrentGameState(Running);
			}
			break;
		}
		case GameOver:
		{
			eventHandler->Listen();
			break;
		}
		}
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
