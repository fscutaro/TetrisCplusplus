#include "SDLRenderer.h"
#include "../DrawingManager.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_rect.h>

Renderer::Renderer(char* title, int width, int height)
{
	if ( ( SDL_Init( SDL_INIT_VIDEO ) > -1 ) && ( IMG_Init( IMG_INIT_PNG ) > -1 ) )
	{
		_window		   = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );
		_windowSurface = SDL_GetWindowSurface( _window );
		_renderer	   = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
		SDL_SetRenderDrawColor( _renderer, 0xff,0xff,0xff,0xff);
	}
	else
	{
		//TODO:: THROW ERROR
		std::cout<<"ERROR LOADING SDL"<<std::endl;
	}
}

Renderer::~Renderer()
{
	SDL_DestroyWindow( _window );
	SDL_DestroyRenderer( _renderer );

	_window		   = nullptr;
	_renderer	   = nullptr;
	_windowSurface = nullptr;

	SDL_Quit();
	IMG_Quit();
}

void Renderer::Draw()
{
	int itemsCount = DrawingManager::getInstance()->getLength();

	SpriteRenderer* r;

    SDL_RenderClear( _renderer );

	for	( int i = 0 ; i < itemsCount; i++ )
	{
		r = DrawingManager::getInstance()->getItemAt( i )->getRenderer();
		//Render texture to screen
		SDL_RenderCopy( _renderer, r->getTexture(), r->getSourceRect(), r->getDestRect() );
	}


	r = nullptr;
    //Update screen
    SDL_RenderPresent( _renderer );

}