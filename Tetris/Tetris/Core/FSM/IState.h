#pragma once
#include "../Processing/IUpdateable.h"
#include "../Display/Sprite.h"

class IState:IUpdateable
{
public:
	virtual void Start()						  = 0;
	virtual void Update(float dt)				  = 0;
	virtual void Sleep()						  = 0;
	virtual char* getName()						  = 0;
	virtual Sprite* addChild( Sprite* sprite )	  = 0;
	virtual Sprite* removeChild( Sprite* sprite ) = 0;
protected:
	char* _name;
	int _childCount;
};
