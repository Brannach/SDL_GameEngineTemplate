#pragma once

#include <list>

#include <SDL.h>
#include <SDL_image.h>

#include "EventHandler.h"

#include "MainApplication.h"
#include "GameMap.h"
#include "MapParser.h"
#include "TextureRenderer.h"
#include "Actor.h"
#include "Gameplay.h"

using namespace std;

class Engine
{
public:
	static Engine* GetInstance()
	{
		if (EngineInstance != nullptr) return EngineInstance;
		else return EngineInstance = new Engine();
	}

	bool Init();
	void Run();
	void LoadScene();
	void Update();
	void Render();
	void Quit();
	inline SDL_Renderer* GetRenderer() { return EngineMainApplication->MainWindowRenderer; }
	inline MainApplication* GetMainApplication() { return EngineMainApplication; }
	inline list<Actor*> GetRenderedActors() { return RenderActor; }
	inline void RemoveRenderedActor(Actor* actor) { RenderActor.remove(actor); }
	inline void AddRenderedActor(Actor* actor) { RenderActor.push_back(actor); }
	inline GameMap* GetCurrentGameMap() { return CurrentGameMap; }
	inline TemplateGameplayRules* GetGameplayRules() { return GameplayRules; }

private:
	GameMap* CurrentGameMap;
	MainApplication* EngineMainApplication;
	static Engine* EngineInstance;
	bool IsEngineRunning = false;
	list<Actor*> RenderActor;
	TemplateGameplayRules* GameplayRules;
};

