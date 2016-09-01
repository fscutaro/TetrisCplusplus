#include "SDLEventManager.h"
#include "../Constants.h"
#include <SDL.h>

SDLEventManager* SDLEventManager::_instance;

SDLEventManager::SDLEventManager(void)
{
	_currentEvent = new SDL_Event();
}


SDLEventManager::~SDLEventManager(void)
{
	SAFE_DELETE_OBJECT( _currentEvent );
}

SDLEventManager* SDLEventManager::getInstance()
{

	if( _instance == nullptr )
	{
		_instance = new SDLEventManager();
	}

	return _instance;
}

int SDLEventManager::pollEvent()
{
	return SDL_PollEvent( _currentEvent );
}


SDL_Event* SDLEventManager::getCurrentEvent()
{
	return _currentEvent;
}
