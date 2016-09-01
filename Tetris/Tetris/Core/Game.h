#pragma once

#include <SDL.h>
#include "Rendering/Renderer.h"
#include "FSM\IState.h"
#include "FSM\StateMachine.h"
#include <vector>
#include "Time\GameTimer.h"
#include "Events\EventDispatcher.h"

class Game:EventDispatcher
{
public:
	Game(char* name, int width, int height, int frameRate, std::vector<IState*>* states);
	~Game();
	void OnEventHandled( const char* eventName );
private:
	Renderer* _renderer;
	StateMachine* _stateMachine;
	void _Update( float deltaTime );
	void _Draw();
	GameTimer* _timer;
};
