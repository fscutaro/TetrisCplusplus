#include "EventDispatcher.h"
#include "EventObserver.h"


const char* EventDispatcher::ENTER_FRAME = "enterFrame";
const char* EventDispatcher::EXIT_FRAME  = "exitFrame";

EventDispatcher::EventDispatcher(void)
{
}

EventDispatcher::~EventDispatcher(void)
{
}

void EventDispatcher::addEventListener(const char* eventName)
{
	EventObserver::getInstance()->Add( eventName, this );
}

void EventDispatcher::removeEventListener(const char* eventName)
{
	EventObserver::getInstance()->Remove( eventName, this );
}

void EventDispatcher::dispatchEvent(const char* eventName)
{
	EventObserver::getInstance()->Dispatch( eventName );
}