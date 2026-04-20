#include "Engine.h"
#include "..\Entities\BouncingBall.h"
#include "..\Entities\Brick.h"
#include "..\Entities\Paddle.h"
#include "..\Entities\Health.h"
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
	LoadScene();

	GameplayRules->SetCurrentGameState(Running);
	return true;
}

void Engine::LoadScene()
{
	TextureRenderer::GetInstance()->Load("ball", "./Resources/Actors/ball_marble.png", GetRenderer());
	TextureRenderer::GetInstance()->Load("paddle", "./Resources/Actors/paddle.png", GetRenderer());
	TextureRenderer::GetInstance()->Load("health", "./Resources/Actors/health.png", GetRenderer());
	BouncingBall* Ball = new BouncingBall(Properties("ball", 400, 475, 24, 24));
	Paddle* GamePaddle = new Paddle(Properties("paddle", 350, 500, 100, 25));
	Health* PlayerHealth = new Health(Properties("health", 700, 550, 20, 20));
	
	RenderActor.push_back(unique_ptr<Actor>(Ball));
	RenderActor.push_back(unique_ptr<Actor>(GamePaddle));
	RenderActor.push_back(unique_ptr<Actor>(PlayerHealth));

	AddGameMap(unique_ptr<GameMap>(MapParser::GetInstance()->Load("Map01", "./Resources/Maps/Map01.tmx")));
	AddGameMap(unique_ptr<GameMap>(MapParser::GetInstance()->Load("Map02", "./Resources/Maps/Map02.tmx")));
	AddGameMap(unique_ptr<GameMap>(MapParser::GetInstance()->Load("Map03", "./Resources/Maps/Map03.tmx")));
	GameMapIterator = GameMaps.begin();
	(*GameMapIterator)->Render();
}

void Engine::Run()
{
	EventHandler& MainEventHandler = EventHandler::GetInstance();
	GameplayRules = make_unique<TemplateGameplayRules>(TemplateGameplayRules(525));
	while (IsEngineRunning)
	{
		Ticker::GetInstance()->Tick();
		float delta = Ticker::GetInstance()->GetDeltaTime();
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
			if (CountActorsByType<Brick>() == 0)
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
	for (const auto& anActor : RenderActor)
	{
		anActor->Update(delta);
	}
}

void Engine::Render()
{
	ResetViewport();
	
	for (const auto& anActor : RenderActor)
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
	if (EventHandler::GetInstance().GetKeyDown(keyCode) == 1)
	{
		return true;
	}
	EngineTextPrinter->PrintText(message, x, y);
	SDL_RenderPresent(GetRenderer());
	return false;
}
