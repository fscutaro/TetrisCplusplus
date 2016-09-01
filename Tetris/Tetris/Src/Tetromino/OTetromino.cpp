#include "OTetromino.h"
#include <vector>
#include "../../Core/FSM/IState.h"

OTetromino::OTetromino(IState* stateInstance):Tetromino(stateInstance)
{
	_maxRotations = 1;

	_grid = new vector<vector<vector<int>*>*>();

	vector<vector<int>*>* first = new vector<vector<int>*>();
	first->push_back( CreateRow( _columns, 1, 1, 0, 0 ) );
	first->push_back( CreateRow( _columns, 1, 1, 0, 0 ) );
	first->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );
	first->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );

	_grid->push_back( first );

	first  = nullptr;

	_spriteURL = "assets/Gameplay/Tetromino/O.png";
}

OTetromino::~OTetromino(void)
{
}


