#include "MainApplication.h"

MainApplication::MainApplication(string windowName, int width, int height)
{
	CreateApplication(windowName, width, height);
	MainWindowDimension.width = width;
	MainWindowDimension.height = height;
	MainWindowRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}

bool MainApplication::CreateApplication(string windowName, int width, int height)
{
	MainWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (MainWindow == NULL)
	{
		SDL_Log("Couldn't create main window");
		return false;
	}
    return true;
}

bool MainApplication::DestroyApplication()
{
	SDL_DestroyRenderer(MainWindowRenderer);
	SDL_DestroyWindow(MainWindow);
	return true;
}

bool MainApplication::ClearBackground()
{

    return false;
}

bool MainApplication::SetWindowName(string windowName)
{
    return false;
}
