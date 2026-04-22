#pragma once
#include <string>
#include <SDL.h>
#include "TextPrinter.h"

class LevelManager;

class ViewRenderer
{
public:
    ViewRenderer(SDL_Renderer* renderer, LevelManager& levelManager);

    void Render();
    void ResetViewport();
    bool DisplayModalMessage(SDL_Scancode keyCode, std::string message, int x, int y);

private:
    SDL_Renderer* mRenderer;
    LevelManager& mLevelManager;
    TextPrinter mTextPrinter;
};
