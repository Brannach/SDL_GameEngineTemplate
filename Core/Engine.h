#pragma once

#include <list>
#include <typeinfo>

#include <SDL.h>
#include <SDL_image.h>

#include "EventHandler.h"
#include "MainApplication.h"
#include "..\Map\GameMap.h"
#include "..\Map\MapParser.h"
#include "..\Rendering\TextureRenderer.h"
#include "..\Entities\Actor.h"
#include "Gameplay.h"
#include "..\Rendering\TextPrinter.h"

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
	void Update(float delta);
	void Render();
	void ResetViewport();
	void Quit();
	bool DisplayModalMessage(SDL_Scancode keyCode, string message, int x, int y);

	template <class T>
	int CountActorsByType();

	inline SDL_Renderer* GetRenderer() { return EngineMainApplication->MainWindowRenderer; }
	inline MainApplication* GetMainApplication() { return EngineMainApplication.get(); }

	inline const list<unique_ptr<Actor>>& GetRenderedActors() { return RenderActor; }
	inline void RemoveRenderedActor(Actor* actor) { erase_if(RenderActor,[actor](const unique_ptr<Actor>& a) { return a.get() == actor; }); }
	inline void AddRenderedActor(unique_ptr<Actor> actor) { RenderActor.push_back(move(actor)); }
	
	inline void AddGameMap(unique_ptr<GameMap> map) { GameMaps.push_back(move(map)); }

	inline TemplateGameplayRules* GetGameplayRules() { return GameplayRules.get(); }	

private:
	unique_ptr<MainApplication> EngineMainApplication;
	static Engine* EngineInstance;
	bool IsEngineRunning = true;
	list<unique_ptr<Actor>> RenderActor;
	vector<unique_ptr<GameMap>> GameMaps;
	vector<unique_ptr<GameMap>>::iterator GameMapIterator;
	unique_ptr<TemplateGameplayRules> GameplayRules;
	unique_ptr<TextPrinter> EngineTextPrinter;
};

template <class T>
int Engine::CountActorsByType()
{
	int counter = 0;
	for (const auto& actor : RenderActor)
	{
		if (dynamic_cast<T*>(actor.get()) != nullptr)
		{
			counter++;
		}
	};
	return counter;
}