#include "DrawingManager.h"
#include "../Constants.h"
#include <vector>
#include "../Display/Sprite.h"
#include <iostream>

DrawingManager* DrawingManager::_instance;

DrawingManager::DrawingManager(void)
{
	_objectsToDraw = new std::vector<Sprite*>();
}

DrawingManager::~DrawingManager(void)
{
	std::cout<<"~DrawingManager"<<std::endl;
	_objectsToDraw->clear();
	SAFE_DELETE_OBJECT( _objectsToDraw );
}

DrawingManager* DrawingManager::getInstance()
{
	if ( _instance == nullptr )
	{
		_instance = new DrawingManager();
	}
	return _instance;
}

int DrawingManager::getLength()
{
	return _objectsToDraw->size();
}

Sprite* DrawingManager::getItemAt(int index)
{
	return _objectsToDraw->at( index );
}

void DrawingManager::add(Sprite* s)
{
	_objectsToDraw->push_back( s );
}

void DrawingManager::remove(Sprite* s)
{
	int itemsLength = getLength();
	for( int i = 0; i < itemsLength; i++ )
	{
		if( s == getItemAt( i ) )
		{
			std::cout<<"remove at "<<i<<std::endl;
			_objectsToDraw->erase( _objectsToDraw->begin() + i );
			break;
		}
	}	
}