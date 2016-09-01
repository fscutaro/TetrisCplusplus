#pragma once

#include "Rendering/SpriteRenderer.h"
#include "../Processing/IUpdateable.h"

class Sprite:IUpdateable
{
public:
	Sprite(const char* imageURL);
	~Sprite(void);
	void Add();
	void Remove();
	void Update();
	float x;
	float y;
	int getWidth();
	int getHeight();
	void Update(float dt);
	SpriteRenderer* getRenderer();
private:
	SpriteRenderer* _renderer;
	void _updateDestRect();
};

