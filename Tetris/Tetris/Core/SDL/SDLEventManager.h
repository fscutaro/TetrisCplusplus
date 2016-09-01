#pragma once

#include <SDL.h>
class SDLEventManager
{
public:
	SDLEventManager(void);
	~SDLEventManager(void);
	static SDLEventManager* getInstance();
	SDL_Event* getCurrentEvent();
	int pollEvent();
private:
	static SDLEventManager* _instance;
	SDL_Event* _currentEvent;
};

