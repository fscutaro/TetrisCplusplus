#include "State.h"
#include "../Display/Sprite.h"

State::State(char* name)
{
	_name = name;
}


State::~State(void)
{
	if( _childCount > 0 )
	{
		//throw error all children must be cleared
	}
}

void State::Start()
{
}

void State::Update(float dt)
{
}

void State::Sleep()
{
}

char* State::getName()
{
	return _name;
}

Sprite* State::addChild( Sprite* sprite )
{
	sprite->Add();
	_childCount++;
	return sprite;
}

Sprite* State::removeChild( Sprite* sprite )
{
	sprite->Remove();
	_childCount--;
	return sprite;
}
