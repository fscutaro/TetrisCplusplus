#pragma once

#include <vector>
#include "IState.h"
#include "../Processing/IUpdateable.h"

class StateMachine:IUpdateable
{
public:
	StateMachine(void);
	~StateMachine(void);
	void AddState( IState* state );
	static StateMachine* GetInstance();
	void SwitchState( char* name );
	void Update(float dt);
private:
	std::vector<IState*>* _states;
	static StateMachine* _instance;
	IState* _FindState(char* name);
	IState* _currentState;
};

