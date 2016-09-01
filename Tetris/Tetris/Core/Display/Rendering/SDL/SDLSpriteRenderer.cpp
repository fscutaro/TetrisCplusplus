#include <SDL.h>
#include <SDL_image.h>
#include "SDLSpriteRenderer.h"
#include "../../../Constants.h"
#include "../../../Rendering/Renderer.h"
#include <iostream>
#include <SDL_rect.h>


SpriteRenderer::SpriteRenderer(const char* imageURL)
{
	_sourceRect = new SDL_Rect();
	_destRect   = new SDL_Rect();
	_texture	= _getTexture( imageURL );
}

SpriteRenderer::~SpriteRenderer()
{
	std::cout<<"~SpriteRenderer"<<std::endl;

	SDL_DestroyTexture( _texture );
	_texture = nullptr;
	SAFE_DELETE_OBJECT( _sourceRect );
	SAFE_DELETE_OBJECT( _destRect );
}

SDL_Texture* SpriteRenderer::_getTexture( const char* path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
		//TODO: SHOW ERRORS
        std::cout<< "Unable to load image %s! SDL_image Error: %s\n"<< path<<std::endl<<IMG_GetError();
    }
    else
    {
        //Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( SDL_GetRenderer( SDL_GetWindowFromID( 1 ) ), loadedSurface );
        if( newTexture == NULL )
        {
            std::cout<< "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError();
        }
		_sourceRect->w = loadedSurface->w;
		_sourceRect->h = loadedSurface->h;
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

SDL_Texture* SpriteRenderer::getTexture()
{
	return _texture;
}

void SpriteRenderer::updateDestRect(float x, float y)
{
	_destRect->x = x;
	_destRect->y = y;
	_destRect->w = _sourceRect->w;
	_destRect->h = _sourceRect->h;
}

SDL_Rect* SpriteRenderer::getDestRect()
{
	return _destRect;
}

SDL_Rect* SpriteRenderer::getSourceRect()
{
	return _sourceRect;
}

int SpriteRenderer::getWidth()
{
	return _sourceRect->w;
}

int SpriteRenderer::getHeight()
{
	return _sourceRect->h;
}