#pragma once
#include "../../../Events/EventDispatcher.h"

class GameLoop: EventDispatcher
{
public:
	GameLoop( int frameRate );
	~GameLoop(void);
	void OnEventHandled(const char* eventName);
};

