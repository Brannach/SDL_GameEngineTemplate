#pragma once

#include <list>
#include <typeinfo>

#include <SDL.h>
#include <SDL_image.h>

#include "EventHandler.h"
#include "MainApplication.h"
#include "GameMap.h"
#include "MapParser.h"
#include "TextureRenderer.h"
#include "Actor.h"
#include "Gameplay.h"
#include "TextPrinter.h"

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
	void ResetViewport();
	void Quit();
	template <class T>
	int CountActorsByType(T classtype);

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
	bool IsEngineRunning = true;
	list<Actor*> RenderActor;
	TemplateGameplayRules* GameplayRules;
	TextPrinter* EngineTextPrinter;
};

template <class T>
int Engine::CountActorsByType(T classtype)
{
	int counter = 0;
	for (auto actor : RenderActor)
	{
		if (dynamic_cast<T>(actor) != nullptr)
		{
			counter++;
		}
	};
	return counter;
}