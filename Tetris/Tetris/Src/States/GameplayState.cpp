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
const float GameplayState::INPUT_COOLDOWN   = 1;

GameplayState::GameplayState(void):State("Gameplay")
{
}

void GameplayState::Start()
{
	addChild( new Sprite("assets/Gameplay/bg.png") );
	_board = new Board(this);

	_updateDelayCount	= 0;
	_updateDelay		= 5;
	_currentTetromino	= getRandomTetromino();
	_nextTetromino		= getRandomTetromino();

	_currentPressedKey = "";
	_lastPressedKey    = "";
	_inputCooldownCount = 0;

	_currentTetromino->Draw();
	_currentTetromino->SetPos( DESIGN_X_GAP, DESIGN_Y_GAP );

	_nextTetromino->Draw();
	_nextTetromino->SetPos( DESIGN_X_GAP, DESIGN_Y_GAP );

	addEventListener( KeyboardKey::LEFT_ARROW );
	addEventListener( KeyboardKey::RIGHT_ARROW );
	addEventListener( KeyboardKey::UP_ARROW );
	addEventListener( KeyboardKey::DOWN_ARROW );
}

void GameplayState::Sleep()
{
	removeEventListener( KeyboardKey::LEFT_ARROW );
	removeEventListener( KeyboardKey::RIGHT_ARROW );
	removeEventListener( KeyboardKey::UP_ARROW );
	removeEventListener( KeyboardKey::DOWN_ARROW );

	SAFE_DELETE_OBJECT( _board );
	_board = nullptr;
}

void GameplayState::Update(float dt)
{
	_inputCooldownCount += dt;	

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
		strcmp( eventName, KeyboardKey::LEFT_ARROW  ) == 0 ||
		strcmp( eventName, KeyboardKey::RIGHT_ARROW ) == 0 ||
		strcmp( eventName, KeyboardKey::UP_ARROW    ) == 0 ||
		strcmp( eventName, KeyboardKey::DOWN_ARROW  ) == 0
	  )
	{
		if( strcmp( _lastPressedKey, _currentPressedKey ) == 0 )
		{
			if( _inputCooldownCount >= INPUT_COOLDOWN )
			{
				_OnInputHandled( eventName );
			}
		}
		else
		{
			_OnInputHandled( eventName );
		}
	}
}

void GameplayState::_OnInputHandled( const char* eventName )
{
	
	_lastPressedKey = _currentPressedKey;

	if( strcmp( eventName, KeyboardKey::LEFT_ARROW  ) == 0 )
	{
		_currentPressedKey = "left";
		if ( _board->canMove( _currentTetromino, -1 ) )
		{
			_currentTetromino->tileX--;
			_updateCurrentTetrominoPosition();
		}
	}
	
	if( strcmp( eventName, KeyboardKey::RIGHT_ARROW  ) == 0 )
	{
		_currentPressedKey = "right";
		if( _board->canMove( _currentTetromino, 1 ) )
		{
			_currentTetromino->tileX++;
			_updateCurrentTetrominoPosition();
		}
	}

	if( strcmp( eventName, KeyboardKey::UP_ARROW  ) == 0 )
	{
		_currentPressedKey = "up";
		if( _board->canRotate( _currentTetromino ) )
		{
			_currentTetromino->Rotate();
		}
	}

	if( strcmp( eventName, KeyboardKey::DOWN_ARROW  ) == 0 )
	{
		_currentPressedKey = "down";
	}

	_inputCooldownCount = 0;
	//std::cout<<"OnInputHandled()= "<<eventName<<std::endl;
}
