#include "GameTimer.h"
#include <SDL.h>

//TODO:: move this to a separated SDL folder
GameTimer::GameTimer(void)
{
	_elapsedTime		 = 0;
	_previousElapsedTime = 0;
	_deltaTime           = 0;
	_paused				 = true;
}

GameTimer::~GameTimer(void)
{
}

void GameTimer::Start()
{
	_Reset();
	Resume();
}

void GameTimer::Stop()
{
	_Reset();
}

void GameTimer::Pause()
{
	_paused = true;
}

void GameTimer::Resume()
{
	_paused = false;
}

void GameTimer::_Reset()
{
	_elapsedTime		 = SDL_GetTicks();
	_previousElapsedTime = 0;
	_deltaTime           = 0;
}

void GameTimer::Update()
{
	if( _paused ) return;

	_previousElapsedTime = _elapsedTime;
	_elapsedTime		 = SDL_GetTicks();
	_deltaTime	         = ( _elapsedTime - _previousElapsedTime )/100;
}

float GameTimer::getDeltaTime()
{
	return _deltaTime;
}