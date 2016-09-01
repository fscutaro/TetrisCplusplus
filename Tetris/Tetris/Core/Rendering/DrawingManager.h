#pragma once

#include <vector>
#include "../Display/Sprite.h"
class DrawingManager
{
public:
	DrawingManager(void);
	~DrawingManager(void);
	static DrawingManager* getInstance();
	int getLength();
	Sprite* getItemAt( int index );
	void add(Sprite* s);
	void remove( Sprite* s );
private:
	static DrawingManager* _instance;
	std::vector<Sprite*>* _objectsToDraw;
};