#include "Ticker.h"

#include <SDL.h>

Ticker* Ticker::TickerInstance = nullptr;

Ticker::Ticker()
{
}

void Ticker::Tick()
{
	DeltaTime = (float)((SDL_GetTicks() - LastDelta) * (TARGET_FPS / 1000.0));
	if (DeltaTime > TARGET_DELTA)
	{
		DeltaTime = TARGET_DELTA;
	}
	LastDelta = (float)SDL_GetTicks();

}
