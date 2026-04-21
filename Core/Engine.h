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
#include "ILevel.h"
#include "LevelManager.h"
#include "..\Rendering\TextPrinter.h"

using namespace std;

class Engine
{
public:
	static Engine& GetInstance()
	{
		static Engine EngineInstance;
		return EngineInstance;
	}
	
	bool Init();
	void Run();
	void SetupLevels();
	void Update(float delta);
	void Render();
	void ResetViewport();
	void Quit();
	bool DisplayModalMessage(SDL_Scancode keyCode, string message, int x, int y);

	inline SDL_Renderer* GetRenderer() { return EngineMainApplication->MainWindowRenderer; }
	inline MainApplication* GetMainApplication() { return EngineMainApplication.get(); }
	inline void AddRenderedActor(unique_ptr<Actor> actor) { mLevelManager->GetCurrentLevel().AddActor(move(actor)); }
	inline void RemoveRenderedActor(Actor* actor)          { mLevelManager->GetCurrentLevel().RemoveActor(actor); }
	inline const list<unique_ptr<Actor>>& GetRenderedActors() { return mLevelManager->GetCurrentLevel().GetActors(); }
	inline TemplateGameplayRules* GetGameplayRules() { return GameplayRules.get(); }	

private:
	unique_ptr<MainApplication> EngineMainApplication;
	bool IsEngineRunning = true;
	unique_ptr<TemplateGameplayRules> GameplayRules;
	unique_ptr<TextPrinter> EngineTextPrinter;
	int mCurrentLevelIndex = 0;
	unique_ptr<LevelManager> mLevelManager;
};