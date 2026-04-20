#include "EventHandler.h"

EventHandler::EventHandler()
{
	mKeyStates = SDL_GetKeyboardState(nullptr);
}

void EventHandler::Listen()
{
	Engine& engine = Engine::GetInstance();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			engine.Quit();
			break;
		}
		case SDL_KEYDOWN:
		{
			KeyDown();
			break;
		}
		case SDL_KEYUP:
		{
			KeyUp();
			break;
		}
		}
	}
}

bool EventHandler::GetKeyDown(SDL_Scancode key)
{
	if (mKeyStates[key] == 1)
		return true;
	return false;
}

void EventHandler::KeyUp()
{
	mKeyStates = SDL_GetKeyboardState(nullptr);
}

void EventHandler::KeyDown()
{
	mKeyStates = SDL_GetKeyboardState(nullptr);
}

int EventHandler::GetAxisKey(AXIS axis)
{
	switch (axis)
	{
	case HORIZONTAL:
	{
		if (GetKeyDown(SDL_SCANCODE_RIGHT))
		{
			return 1;
		}
		if (GetKeyDown(SDL_SCANCODE_LEFT))
		{
			return -1;
		}
		break;
	}
	case VERTICAL:
	{
		if (GetKeyDown(SDL_SCANCODE_UP))
		{
			return -1;
		}
		if (GetKeyDown(SDL_SCANCODE_DOWN))
		{
			return 1;
		}
		break;
	}
	default:
		return 0;
	}
	return 0;
}
