#include "SDLKeyboardController.h"
#include "../../../SDL/SDLEventManager.h"
#include "../KeyboardKey.h"


KeyboardController::KeyboardController(void)
{
}

KeyboardController::~KeyboardController(void)
{
}

void KeyboardController::Update()
{
	SDL_Event* currentEvent = SDLEventManager::getInstance()->getCurrentEvent();

	if( currentEvent->type == SDL_KEYDOWN )
	{
		switch( currentEvent->key.keysym.sym )
		{
			case SDLK_UP:
				dispatchEvent( KeyboardKey::UP_ARROW );
				break;
			case SDLK_DOWN:
				dispatchEvent( KeyboardKey::DOWN_ARROW );
				break;
			case SDLK_LEFT:
				dispatchEvent( KeyboardKey::LEFT_ARROW );
				break;
			case SDLK_RIGHT:
				dispatchEvent( KeyboardKey::RIGHT_ARROW );
				break;
		}
	}
}

void KeyboardController::OnEventHandled(const char* name)
{
	//do nothing. TODO: ABSTRACT EVENT DISPATCHER FROM EVENT HANDLER CALLBACK, BUT KEEP EVENT HANDLER CALLBACK MANDATORY FOR THE CLASSES THAT NEEDS TO LISTEN TO EVENTS
}

