#include "ViewRenderer.h"
#include "../Core/LevelManager.h"
#include "../Core/EventHandler.h"

ViewRenderer::ViewRenderer(SDL_Renderer* renderer, LevelManager& levelManager)
    : mRenderer(renderer), mLevelManager(levelManager), mTextPrinter(renderer) {}

void ViewRenderer::Render()
{
    ResetViewport();
    mLevelManager.GetCurrentLevel().Render();
    SDL_RenderPresent(mRenderer);
}

void ViewRenderer::ResetViewport()
{
    SDL_SetRenderDrawColor(mRenderer, 35, 35, 35, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mRenderer);
}

bool ViewRenderer::DisplayModalMessage(SDL_Scancode keyCode, std::string message, int x, int y)
{
    if (EventHandler::GetInstance().GetKeyDown(keyCode) == 1)
        return true;
    mTextPrinter.PrintText(message, x, y);
    SDL_RenderPresent(mRenderer);
    return false;
}
