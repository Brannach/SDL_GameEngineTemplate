#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "EventHandler.h"
#include "MainApplication.h"
#include "TextureRenderer.h"

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
	void Quit();
	inline SDL_Renderer* GetRenderer() { return EngineMainApplication->MainWindowRenderer; }

private:
	TextureRenderer* EngineTextureRenderer;
	MainApplication* EngineMainApplication;
	static Engine* EngineInstance;
	bool IsEngineRunning = false;
};

