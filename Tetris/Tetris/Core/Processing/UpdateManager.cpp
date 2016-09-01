#include "UpdateManager.h"
#include "../Constants.h"
#include <vector>

UpdateManager* UpdateManager::_instance;

UpdateManager::UpdateManager(void)
{
	_objectsToUpdate = new std::vector<IUpdateable*>();
}

UpdateManager::~UpdateManager(void)
{
	std::cout<<"~UpdateManager"<<std::endl;
	SAFE_DELETE_OBJECT( _instance );
	_objectsToUpdate->clear();
	SAFE_DELETE_OBJECT( _objectsToUpdate );
}

UpdateManager* UpdateManager::getInstance()
{
	if( _instance == nullptr )
	{
		_instance = new UpdateManager();
	}
	return _instance;
}

std::vector<IUpdateable*>* UpdateManager::getUpdateables()
{
	return _objectsToUpdate;
}

void UpdateManager::Update( float dt )
{
	std::vector<IUpdateable*>* updateables = getInstance()->getUpdateables();
	int itemsLength = updateables->size();
	for( int i = 0; i < itemsLength; i++ )
	{
		updateables->at( i )->Update( dt );
	}
	updateables = nullptr;
}

void UpdateManager::add(IUpdateable* s)
{
	_objectsToUpdate->push_back( s );
}

void UpdateManager::remove(IUpdateable* s)
{
	int itemsLength = _objectsToUpdate->size();
	for( int i = 0; i < itemsLength; i++ )
	{
		if( s == _objectsToUpdate->at( i ) )
		{
			std::cout<<"remove at "<<i<<std::endl;
			_objectsToUpdate->erase( _objectsToUpdate->begin() + i );
			break;
		}
	}	
}