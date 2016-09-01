#pragma once
#include "../ISpriteRenderer.h"
#include <SDL.h>
#include <SDL_rect.h>

class SpriteRenderer:ISpriteRenderer
{
public:
	SpriteRenderer::SpriteRenderer(const char* imageURL);
	SpriteRenderer::~SpriteRenderer();
	SDL_Texture* getTexture();
	void updateDestRect(float x, float y);
	SDL_Rect* getDestRect();
	SDL_Rect* getSourceRect();
	int getWidth();
	int getHeight();
private:
	SDL_Texture* _getTexture( const char* path );
	SDL_Rect* _sourceRect;
	SDL_Rect* _destRect;
	//RENDERER VARS
	SDL_Texture* _texture;
};