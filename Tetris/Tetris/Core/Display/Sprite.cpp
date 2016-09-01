#include "Sprite.h"
#include "../Constants.h"
#include "Rendering/SpriteRenderer.h"
#include "../Rendering/DrawingManager.h"
#include "../Processing/UpdateManager.h"
#include <iostream>

Sprite::Sprite(const char* imageURL)
{
	x = 0;
	y = 0;
	_renderer = new SpriteRenderer( imageURL );
}

Sprite::~Sprite(void)
{
	std::cout<<"~Sprite"<<std::endl;
	SAFE_DELETE_OBJECT( _renderer );
}

SpriteRenderer* Sprite::getRenderer()
{
	return _renderer;
}

void Sprite::Add()
{
	DrawingManager::getInstance()->add( this );
	UpdateManager::getInstance()->add( this );
}

void Sprite::Remove()
{
	DrawingManager::getInstance()->remove( this );
	UpdateManager::getInstance()->remove( this );
}

void Sprite::Update(float dt)
{
	_renderer->updateDestRect( x, y );
}

int Sprite::getWidth()
{
	return _renderer->getWidth();
}

int Sprite::getHeight()
{
	return _renderer->getHeight();
}