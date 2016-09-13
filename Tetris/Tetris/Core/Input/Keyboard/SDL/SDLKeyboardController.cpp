#include "SDLKeyboardController.h"
#include "../../../SDL/SDLEventManager.h"
#include "../KeyboardKey.h"
#include <iostream>

KeyboardController::KeyboardController(void)
{
}

KeyboardController::~KeyboardController(void)
{
}

void KeyboardController::Update()
{
	SDL_Event* currentEvent = SDLEventManager::getInstance()->getCurrentEvent();

	bool keyStateChanged = currentEvent->type == SDL_KEYDOWN || currentEvent->type == SDL_KEYUP;

	//TODO:: OPTIMIZE THIS. SDL_KEYUP IS ALWAYS FIRED
	if( keyStateChanged )
	{
		switch( currentEvent->key.keysym.sym )
		{
			case SDLK_UP:
				dispatchEvent( ( currentEvent->type == SDL_KEYDOWN ) ? KEY_DOWN::KeyboardKey::UP_ARROW : KEY_UP::KeyboardKey::UP_ARROW );
				break;
			case SDLK_DOWN:
				dispatchEvent( ( currentEvent->type == SDL_KEYDOWN ) ? KEY_DOWN::KeyboardKey::DOWN_ARROW : KEY_UP::KeyboardKey::DOWN_ARROW );
				break;
			case SDLK_LEFT:
				dispatchEvent( ( currentEvent->type == SDL_KEYDOWN ) ? KEY_DOWN::KeyboardKey::LEFT_ARROW : KEY_UP::KeyboardKey::LEFT_ARROW );
				break;
			case SDLK_RIGHT:
				dispatchEvent( ( currentEvent->type == SDL_KEYDOWN ) ? KEY_DOWN::KeyboardKey::RIGHT_ARROW : KEY_UP::KeyboardKey::RIGHT_ARROW );
				break;
		}
	}
}

void KeyboardController::OnEventHandled(const char* name)
{
	//do nothing. TODO: ABSTRACT EVENT DISPATCHER FROM EVENT HANDLER CALLBACK, BUT KEEP EVENT HANDLER CALLBACK MANDATORY FOR THE CLASSES THAT NEEDS TO LISTEN TO EVENTS
}

