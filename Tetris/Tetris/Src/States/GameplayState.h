#pragma once
#include "../../Core/FSM/State.h"
#include "../Utils/Board.h"
#include "../Tetromino/Tetromino.h"
#include "../../Core/Events/EventDispatcher.h"

class GameplayState:public State, EventDispatcher
{
public:
	GameplayState(void);
	~GameplayState(void);
	void Start();
	void Sleep();
	void Update(float dt);
	Tetromino* getRandomTetromino();
	void OnEventHandled( const char* eventName );
private:
	Board* _board;
	Tetromino* _currentTetromino;
	Tetromino* _nextTetromino;
	float _updateDelayCount;
	float _updateDelay;
	static const float DESIGN_X_GAP;
	static const float DESIGN_Y_GAP;
	static const float NORMAL_UPDATE_DELAY_TIME;
	static const float SPEED_UP_UPDATE_DELAY_TIME;
	static const int DESIGN_TILE_SIZE;
	void _OnInputHandled( const char* eventName );
	void _updateCurrentTetrominoPosition();
	bool _upArrowPressed;
	bool _leftArrowPressed;
	bool _rightArrowPressed;
};

