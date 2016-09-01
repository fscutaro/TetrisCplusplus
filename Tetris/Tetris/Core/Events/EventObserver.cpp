#include "EventObserver.h"
#include <map>
#include <vector>
#include "../Constants.h"
#include "IEventDispatcher.h"

using namespace std;

EventObserver* EventObserver::_instance;

EventObserver::EventObserver(void)
{
	_subscriptions = new map< const char*, vector<IEventDispatcher*>*>();
}

EventObserver::~EventObserver(void)
{
	_subscriptions->clear();
	SAFE_DELETE_OBJECT( _subscriptions );
	SAFE_DELETE_OBJECT( _instance );
}

void EventObserver::Add( const char* eventName, IEventDispatcher* subscriptor)
{
	vector<IEventDispatcher*>* subscriptions = ( _subscriptions->count( eventName ) == 1 ) ? _subscriptions->at( eventName ) : nullptr;
	if( subscriptions == nullptr )
	{
		subscriptions = new vector<IEventDispatcher*>();
		pair<const char*, vector<IEventDispatcher*>* > keyValue( eventName, subscriptions );
		_subscriptions->insert(_subscriptions->begin(), keyValue );
		_subscriptions->at(eventName) = subscriptions;
	}
	else
	{
		//we check if this event wasn't already registered for this IEventDispatcher
		int numSubscriptions = subscriptions->size();
		for( int i = 0; i < numSubscriptions; i++ )
		{
			if( subscriptions->at(i) == subscriptor )
			{
				std::cout<<"ERROR:: eventName= "<<eventName<<" already registered for class "<<subscriptor<<std::endl;
				return;
			}
		}
	}

	subscriptions->push_back( subscriptor );
}

void EventObserver::Remove( const char* eventName, IEventDispatcher* subscriptor)
{
	vector<IEventDispatcher*>* subscriptions = ( _subscriptions->count( eventName ) == 1 ) ? _subscriptions->at( eventName ) : nullptr;
	if( subscriptions == nullptr )
	{
		std::cout<<"ERROR:: eventName= "<<eventName<<" event list is empty "<<std::endl;
		return;
	}
	else
	{
		int numSubscriptions = subscriptions->size();
		for( int i = 0; i < numSubscriptions; i++ )
		{
			if( subscriptions->at(i) == subscriptor )
			{
				subscriptions->erase( subscriptions->begin() +  i );
				break;
			}
		}
	}

	//We free memory used for event listeners that has no subscriptions
	if( subscriptions->size() == 0 )
	{
		SAFE_DELETE_OBJECT(_subscriptions->at(eventName));
	}
}


void EventObserver::Dispatch( const char* eventName )
{
	vector<IEventDispatcher*>* subscriptions = ( _subscriptions->count( eventName ) == 1 ) ? _subscriptions->at( eventName ) : nullptr;

	if( subscriptions != nullptr )
	{
		int numSubscriptions = subscriptions->size();
		for( int i = 0; i < numSubscriptions; i++ )
		{
			subscriptions->at( i )->OnEventHandled( eventName );
		}
	}
}

EventObserver* EventObserver::getInstance()
{
	if( _instance == nullptr )
	{
		_instance = new EventObserver();
	}

	return _instance;
}

