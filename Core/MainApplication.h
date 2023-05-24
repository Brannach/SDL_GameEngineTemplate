#pragma once

#include <string>
#include <SDL.h>
#include "Geometry2d.h"
using namespace std;

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGTH 600

class MainApplication
{
public:
	MainApplication(string windowName = "Default", int width = DEFAULT_SCREEN_WIDTH, int height = DEFAULT_SCREEN_HEIGTH);
	bool CreateApplication(string windowName = "Default", int width = DEFAULT_SCREEN_WIDTH, int height = DEFAULT_SCREEN_HEIGTH);
	bool DestroyApplication();

	bool ClearBackground();
	bool SetWindowName(string windowName);
	Dimension2d<int> MainWindowDimension;

private:
	SDL_Window* MainWindow;
	SDL_Renderer* MainWindowRenderer;
};

