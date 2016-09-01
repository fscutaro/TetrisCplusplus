#pragma once

#include <vector>
#include "IUpdateable.h"
class UpdateManager
{
public:
	UpdateManager(void);
	~UpdateManager(void);
	static UpdateManager* getInstance();
	void add(IUpdateable* updateable);
	void remove( IUpdateable* updateable );
	std::vector<IUpdateable*>* getUpdateables();
	static void Update( float dt );
private:
	static UpdateManager* _instance;
	std::vector<IUpdateable*>* _objectsToUpdate;
};

