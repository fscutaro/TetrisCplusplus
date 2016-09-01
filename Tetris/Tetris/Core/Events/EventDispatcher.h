#pragma once
#include "IEventDispatcher.h"
class EventDispatcher:public IEventDispatcher
{
public:
	EventDispatcher(void);
	~EventDispatcher(void);
	void addEventListener( const char* eventName );
	void removeEventListener( const char* eventName );
	void dispatchEvent( const char* eventName );
	static const char* ENTER_FRAME;
	static const char* EXIT_FRAME;
};