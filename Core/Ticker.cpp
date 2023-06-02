#include "Ticker.h"

#include <SDL.h>

Ticker* Ticker::TickerInstance = nullptr;

Ticker::Ticker()
{
}

void Ticker::Tick()
{
	DeltaTime = (SDL_GetTicks() - LastDelta) * (TARGET_FPS / 1000.0);
	if (DeltaTime > TARGET_DELTA)
	{
		DeltaTime = TARGET_DELTA;
	}
	LastDelta = SDL_GetTicks();

}
