#include "EventHandler.h"

void EventHandler::Listen()
{
	Engine* engine = Engine::GetInstance();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			engine->Quit();
			break;
		}
		
		}
	}
}
