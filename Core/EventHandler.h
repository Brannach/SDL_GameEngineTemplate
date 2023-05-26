#pragma once

#include <SDL.h>

#include "Engine.h"

enum AXIS { HORIZONTAL, VERTICAL };

class EventHandler
{
public:
	void Listen();
	static EventHandler* GetInstance()
	{
		if (EventHandlerInstance != nullptr) return EventHandlerInstance;
		else return EventHandlerInstance = new EventHandler();
	}
	bool GetKeyDown(SDL_Scancode key);
	int GetAxisKey(AXIS axis);

private:
	EventHandler();
	void KeyUp();
	void KeyDown();
	const Uint8* mKeyStates;
	static EventHandler* EventHandlerInstance;
};

