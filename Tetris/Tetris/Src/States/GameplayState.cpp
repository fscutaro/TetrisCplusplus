#include "GameplayState.h"
#include "../../Core/Display/Sprite.h"
#include "../../Core/Constants.h"
#include "../Tetromino/LTetromino.h"
#include "../Tetromino/OTetromino.h"
#include "../Tetromino/JTetromino.h"
#include "../Tetromino/STetromino.h"
#include "../Tetromino/TTetromino.h"
#include "../Tetromino/ZTetromino.h"
#include "../Tetromino/ITetromino.h"
#include "../../Core/Input/Keyboard/KeyboardKey.h"
#include <iostream>
#include <random>

const float GameplayState::DESIGN_X_GAP     = 11.5f;
const float GameplayState::DESIGN_Y_GAP     = 10;
const int   GameplayState::DESIGN_TILE_SIZE = 29;
const float GameplayState::NORMAL_UPDATE_DELAY_TIME   = 5;
const float GameplayState::SPEED_UP_UPDATE_DELAY_TIME = .3f;

GameplayState::GameplayState(void):State("Gameplay")
{
}

void GameplayState::Start()
{
	addChild( new Sprite("assets/Gameplay/bg.png") );
	_board = new Board(this);

	_updateDelayCount	= 0;
	_updateDelay		= NORMAL_UPDATE_DELAY_TIME;
	_currentTetromino	= getRandomTetromino();
	_nextTetromino		= getRandomTetromino();

	_currentTetromino->Draw();
	_currentTetromino->SetPos( DESIGN_X_GAP, DESIGN_Y_GAP );

	_nextTetromino->Draw();
	_nextTetromino->SetPos( DESIGN_X_GAP, DESIGN_Y_GAP );

	addEventListener( KEY_DOWN::KeyboardKey::LEFT_ARROW );
	addEventListener( KEY_UP::KeyboardKey::LEFT_ARROW );

	addEventListener( KEY_DOWN::KeyboardKey::RIGHT_ARROW );
	addEventListener( KEY_UP::KeyboardKey::RIGHT_ARROW );

	addEventListener( KEY_DOWN::KeyboardKey::UP_ARROW );
	addEventListener( KEY_UP::KeyboardKey::UP_ARROW );

	addEventListener( KEY_DOWN::KeyboardKey::DOWN_ARROW );
	addEventListener( KEY_UP::KeyboardKey::DOWN_ARROW );
}

void GameplayState::Sleep()
{
	removeEventListener( KEY_DOWN::KeyboardKey::LEFT_ARROW );
	removeEventListener( KEY_UP::KeyboardKey::LEFT_ARROW );

	removeEventListener( KEY_DOWN::KeyboardKey::RIGHT_ARROW );
	removeEventListener( KEY_UP::KeyboardKey::RIGHT_ARROW );

	removeEventListener( KEY_DOWN::KeyboardKey::UP_ARROW );
	removeEventListener( KEY_UP::KeyboardKey::UP_ARROW );

	removeEventListener( KEY_DOWN::KeyboardKey::DOWN_ARROW );
	removeEventListener( KEY_UP::KeyboardKey::DOWN_ARROW );

	SAFE_DELETE_OBJECT( _board );
	_board = nullptr;
}

void GameplayState::Update(float dt)
{
	_updateDelayCount += dt;
	if( _updateDelayCount >= _updateDelay )
	{
		if(! _board->tetrominoIsGrounded(_currentTetromino))
		{
			int tileYPos = _currentTetromino->GetY() * Board::ROWS;
			int tileXPos = _currentTetromino->GetX() * Board::COLUMNS;
			_updateDelayCount = 0;
			
			_currentTetromino->tileY++;
			_updateCurrentTetrominoPosition();
		}
		else
		{
			_board->placeTetromino( _currentTetromino );
			_currentTetromino = _nextTetromino;
			_nextTetromino = getRandomTetromino();
			_nextTetromino->Draw();
		}
	}
}

GameplayState::~GameplayState(void)
{
	SAFE_DELETE_OBJECT( _currentTetromino );
	_currentTetromino = nullptr;
	SAFE_DELETE_OBJECT( _nextTetromino );
	_nextTetromino    = nullptr;
}

void GameplayState::_updateCurrentTetrominoPosition()
{
	_currentTetromino->SetPos( ( ( _currentTetromino->tileX * DESIGN_TILE_SIZE ) + DESIGN_X_GAP ), ( ( _currentTetromino->tileY * DESIGN_TILE_SIZE ) + DESIGN_Y_GAP ) );
}

//TODO: USE REAL RANDOM NUMBERS.
Tetromino* GameplayState::getRandomTetromino()
{
	int max = 6;
	int min = 0;

	int randomN = rand() % 7;

	return new ITetromino( this );

	switch( randomN )
	{
		case 0:
			return new JTetromino( this );
		case 1:
			return new LTetromino( this );
		case 2:
			return new ITetromino( this );
		case 3:
			return new OTetromino( this );
		case 4:
			return new STetromino( this );
		case 5:
			return new TTetromino( this );
		case 6:
			return new ZTetromino( this );
	}
}

void GameplayState::OnEventHandled( const char* eventName )
{
	//std::cout<<"event= "<<eventName<<std::endl;
	if(
		strcmp( eventName, KEY_DOWN::KeyboardKey::LEFT_ARROW  ) == 0 ||
		strcmp( eventName, KEY_UP::KeyboardKey::LEFT_ARROW ) == 0 ||
		strcmp( eventName, KEY_DOWN::KeyboardKey::RIGHT_ARROW    ) == 0 ||
		strcmp( eventName, KEY_UP::KeyboardKey::RIGHT_ARROW  ) == 0 ||
		strcmp( eventName, KEY_DOWN::KeyboardKey::UP_ARROW  ) == 0 ||
		strcmp( eventName, KEY_UP::KeyboardKey::UP_ARROW  ) == 0 ||
		strcmp( eventName, KEY_DOWN::KeyboardKey::DOWN_ARROW  ) == 0 ||
		strcmp( eventName, KEY_UP::KeyboardKey::DOWN_ARROW  ) == 0
	  )
	{
		_OnInputHandled( eventName );
	}
}

void GameplayState::_OnInputHandled( const char* eventName )
{
	
	if( strcmp( eventName, KEY_DOWN::KeyboardKey::LEFT_ARROW  ) == 0 && !_leftArrowPressed )
	{
		if ( _board->canMove( _currentTetromino, -1 ) )
		{
			_currentTetromino->tileX--;
			_updateCurrentTetrominoPosition();
		}
		_leftArrowPressed = true;
	}

	if( strcmp( eventName, KEY_UP::KeyboardKey::LEFT_ARROW  ) == 0 )
	{
		_leftArrowPressed = false;
	}

	if( strcmp( eventName, KEY_DOWN::KeyboardKey::RIGHT_ARROW  ) == 0 && !_rightArrowPressed )
	{
		if( _board->canMove( _currentTetromino, 1 ) )
		{
			_currentTetromino->tileX++;
			_updateCurrentTetrominoPosition();
		}
		_rightArrowPressed = true;
	}

	if( strcmp( eventName, KEY_UP::KeyboardKey::RIGHT_ARROW  ) == 0 )
	{
		_rightArrowPressed = false;
	}

	if( strcmp( eventName, KEY_DOWN::KeyboardKey::UP_ARROW  ) == 0 && !_upArrowPressed )
	{
		if( _board->canRotate( _currentTetromino ) )
		{
			_currentTetromino->Rotate();
			
		}
		_upArrowPressed = true;
	}

	if( strcmp( eventName, KEY_UP::KeyboardKey::UP_ARROW  ) == 0 )
	{
		_upArrowPressed = false;
	}

	if( strcmp( eventName, KEY_DOWN::KeyboardKey::DOWN_ARROW  ) == 0 )
	{
		_updateDelay = SPEED_UP_UPDATE_DELAY_TIME;
	}

	if( strcmp( eventName, KEY_UP::KeyboardKey::DOWN_ARROW  ) == 0 )
	{
		_updateDelay = NORMAL_UPDATE_DELAY_TIME;
	}
	
	//std::cout<<"OnInputHandled()= "<<eventName<<std::endl;
}
