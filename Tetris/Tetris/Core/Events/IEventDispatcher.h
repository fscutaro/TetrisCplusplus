#pragma once
class IEventDispatcher
{
public:
	void addEventListener( const char* eventName );
	void removeEventListener( const char* eventName );
	void dispatchEvent( const char* eventName );
	virtual void OnEventHandled( const char* eventName ) = 0;
};