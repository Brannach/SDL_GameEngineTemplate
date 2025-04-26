#include "Engine.h"
#include "..\Entities\BouncingBall.h"
#include "..\Entities\Brick.h"
#include "..\Entities\Paddle.h"
#include "..\Entities\Health.h"
#include "..\Core\Ticker.h"

Engine* Engine::EngineInstance = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG) != 0)
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
	EngineMainApplication = new MainApplication("Engine Template");
	EngineTextPrinter = new TextPrinter(GetRenderer());
	LoadScene();

	GameplayRules->SetCurrentGameState(Running);
	return true;
}

void Engine::LoadScene()
{
	TextureRenderer::GetInstance()->Load("ball", "resources/actors/ball_marble.png", GetRenderer());
	TextureRenderer::GetInstance()->Load("paddle", "resources/actors/paddle.png", GetRenderer());
	TextureRenderer::GetInstance()->Load("health", "resources/actors/health.png", GetRenderer());
	BouncingBall* Ball = new BouncingBall(new Properties("ball", 400, 475, 24, 24));
	Paddle* GamePaddle = new Paddle(new Properties("paddle", 350, 500, 100, 25));
	Health* PlayerHealth = new Health(new Properties("health", 700, 550, 20, 20));
	
	RenderActor.push_back(Ball);
	RenderActor.push_back(GamePaddle);
	RenderActor.push_back(PlayerHealth);

	AddGameMap(MapParser::GetInstance()->Load("Map01", "Resources/Maps/Map01.tmx"));
	AddGameMap(MapParser::GetInstance()->Load("Map02", "Resources/Maps/Map02.tmx"));
	GameMapIterator = GameMaps.begin();
	(*GameMapIterator)->Render();
}

void Engine::Run()
{
	EventHandler* MainEventHandler = EventHandler::GetInstance();
	GameplayRules = new TemplateGameplayRules(525);
	while (IsEngineRunning)
	{
		Ticker::GetInstance()->Tick();
		float delta = Ticker::GetInstance()->GetDeltaTime();
		MainEventHandler->Listen();
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
			if (CountActorsByType(new Brick()) == 0)
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
			//Special case for the last level
			if (next(GameMapIterator) == GameMaps.end())
			{
				GameplayRules->SetCurrentGameState(GameComplete);
				break;
			}
			Update(delta);
			ResetViewport();
			if (DisplayModalMessage(SDL_SCANCODE_SPACE, "New Level Unlocked!", 250, 520))
			{
				advance(GameMapIterator, 1);
				if (GameMapIterator != GameMaps.end())
				{
					GameplayRules->SetCurrentGameState(Restarting);
					break;
				}
			}
			
			break;
		}
		case Restarting:
		{
			if (GameMapIterator != GameMaps.end())
			{
				(*GameMapIterator)->Render();
			}
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
	for (Actor* anActor : RenderActor)
	{
		anActor->Update(delta);
	}
}

void Engine::Render()
{
	ResetViewport();
	
	for (Actor* anActor : RenderActor)
	{
		anActor->Draw();
	}
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
	if (EventHandler::GetInstance()->GetKeyDown(keyCode) == 1)
	{
		return true;
	}
	EngineTextPrinter->PrintText(message, x, y);
	SDL_RenderPresent(GetRenderer());
	return false;
}
