#pragma once
#include <map>
#include <vector>
#include "IEventDispatcher.h"
using namespace std;
class EventObserver
{
public:
	EventObserver(void);
	~EventObserver(void);
	void Add( const char* eventName, IEventDispatcher* subscriptor );
	void Remove( const char* eventName, IEventDispatcher* subscriptor );
	void Dispatch( const char* eventName );
	static EventObserver* getInstance();
private:
	map< const char*, vector<IEventDispatcher* >* >* _subscriptions;
	static EventObserver* _instance;
};

