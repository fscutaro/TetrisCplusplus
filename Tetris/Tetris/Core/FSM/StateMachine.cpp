#include "StateMachine.h"
#include "../Constants.h"
#include <vector>
#include "IState.h"
#include <stdio.h>
#include "../Processing/UpdateManager.h"

StateMachine* StateMachine::_instance;

StateMachine::StateMachine(void)
{
	UpdateManager::getInstance()->add( this );
	_states = new std::vector<IState*>();
	_currentState = nullptr;
}

StateMachine::~StateMachine(void)
{
	UpdateManager::getInstance()->remove( this );
	_states->clear();
	SAFE_DELETE_OBJECT( _states );
	_states = nullptr;
	SAFE_DELETE_OBJECT( _instance );
	_instance = nullptr;
	SAFE_DELETE_OBJECT( _currentState );
	_currentState = nullptr;
}

void StateMachine::AddState(IState* state)
{
	_states->push_back( state );
	if( _states->size() == 1 )
	{
		SwitchState( _states->at( 0 )->getName() );
	}
}

StateMachine* StateMachine::GetInstance()
{
	if( _instance == nullptr )
	{
		_instance = new StateMachine();
	}
	return _instance;
}

void StateMachine::Update(float dt)
{
	_currentState->Update( dt );
}

void StateMachine::SwitchState( char* name )
{
	if( _currentState != nullptr )
	{
		_currentState->Sleep();
	}

	_currentState = _FindState( name );
	_currentState->Start();
}

IState* StateMachine::_FindState(char* name)
{
	int statesLength = _states->size();

	IState* state;
	char* stateName;
	for( int i = 0; i < statesLength; i++ )
	{
		state     = _states->at( i );
		stateName = state->getName();
		if( strcmp( stateName, name ) == 0 )
		{
			return state;
		}
	}

	//TODO :: THROW ERROR STATE NOT FOUND
}
