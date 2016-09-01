#pragma once

#include "SDL.h"
#include "../IRenderer.h"

class Renderer:IRenderer
{
public:
	Renderer(char* title, int width, int height);
	~Renderer();
	void Draw();
private:
	SDL_Window* _window;
	SDL_Surface* _windowSurface;
	//RENDERER VARS
	SDL_Renderer* _renderer;
};

