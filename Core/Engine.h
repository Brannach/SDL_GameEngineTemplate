#pragma once

#include <list>

#include <SDL.h>
#include <SDL_image.h>

#include "EventHandler.h"
#include "MainApplication.h"
#include "TextureRenderer.h"
#include "Actor.h"

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
	void Update();
	void Render();
	void Quit();
	static inline SDL_Renderer* GetRenderer() { return EngineMainApplication->MainWindowRenderer; }
	static inline MainApplication* GetMainApplication() { return EngineMainApplication; }

private:
	static MainApplication* EngineMainApplication;
	static Engine* EngineInstance;
	bool IsEngineRunning = false;
	list<Actor*> RenderActor;
};

