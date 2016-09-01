#include "SDLGameLoop.h"
#include <SDL_events.h>
#include <SDL.h>
#include "../../../Events/EventDispatcher.h"
#include "../../../SDL/SDLEventManager.h"
#include "../../../SDL/SDLEventManager.h"
#include "../../../Input/Keyboard/KeyboardInputController.h"

GameLoop::GameLoop( int frameRate )
{
	const int SCREEN_TICKS_PER_FRAME = 1000 / frameRate;

	bool quit = false;

	KeyboardController inputController;

	while( !quit )
	{
		while( SDLEventManager::getInstance()->pollEvent() != 0 )
		{
			if( SDLEventManager::getInstance()->getCurrentEvent()->type == SDL_QUIT )
			{
				quit = true;
			}
		}

		inputController.Update();

		dispatchEvent( ENTER_FRAME );

		SDL_Delay( SCREEN_TICKS_PER_FRAME );

		dispatchEvent( EXIT_FRAME );
	}
}

GameLoop::~GameLoop(void)
{
}

void GameLoop::OnEventHandled(const char* name)
{
	//do nothing. TODO: ABSTRACT EVENT DISPATCHER FROM EVENT HANDLER CALLBACK, BUT KEEP EVENT HANDLER CALLBACK MANDATORY FOR THE CLASSES THAT NEEDS TO LISTEN TO EVENTS
}
