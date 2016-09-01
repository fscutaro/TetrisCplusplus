#include "Game.h"
#include "Constants.h"
#include "Display\Sprite.h"
#include <iostream>
#include "Processing\UpdateManager.h"
#include <vector>
#include "Processing\GameLoop\GameLoop.h"

Game::Game(char* name, int width, int height, int frameRate, std::vector<IState*>* states)
{
	_renderer	  = new Renderer( name, width, height );
	_stateMachine = new StateMachine();

	int statesLength = states->size();
	for( int i = 0 ; i < statesLength; i++  )
	{
		_stateMachine->AddState( states->at( i ) );
	}

	addEventListener( ENTER_FRAME );

	addEventListener( EXIT_FRAME );

	_timer = new GameTimer();

	_timer->Start();

	GameLoop loop( frameRate );
}

void Game::OnEventHandled( const char* eventName )
{
	if( strcmp( eventName, ENTER_FRAME ) == 0 )
	{
		_timer->Update();
		_Update( _timer->getDeltaTime() );
		_Draw();
	}
}

void Game::_Update( float deltaTime )
{
	UpdateManager::Update( deltaTime );
}

void Game::_Draw()
{
	_renderer->Draw();
}

Game::~Game()
{
	removeEventListener( ENTER_FRAME );
	removeEventListener( EXIT_FRAME );

	SAFE_DELETE_OBJECT( _renderer );
	SAFE_DELETE_OBJECT( _stateMachine );
	_stateMachine = nullptr;
	_timer->Stop();
	SAFE_DELETE_OBJECT( _timer );
	_timer = nullptr;
}