#pragma once
#include "IState.h"
class State:public IState
{
public:
	State(char* name);
	~State(void);
	void Start();
	void Update(float dt);
	void Sleep();
	char* getName();
	Sprite* addChild( Sprite* sprite )	 ;
	Sprite* removeChild( Sprite* sprite );
};

