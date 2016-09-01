#include "TTetromino.h"
#include <vector>
#include "../../Core/FSM/IState.h"

TTetromino::TTetromino(IState* stateInstance):Tetromino(stateInstance)
{
	_maxRotations = 3;

	_grid = new vector<vector<vector<int>*>*>();

	vector<vector<int>*>* first = new vector<vector<int>*>();
	first->push_back( CreateRow( _columns, 1, 1, 1, 0 ) );
	first->push_back( CreateRow( _columns, 0, 1, 0, 0 ) );
	first->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );
	first->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );

	vector<vector<int>*>* second = new vector<vector<int>*>();
	second->push_back( CreateRow( _columns, 0, 1, 0, 0 ) );
	second->push_back( CreateRow( _columns, 1, 1, 0, 0 ) );
	second->push_back( CreateRow( _columns, 0, 1, 0, 0 ) );
	second->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );

	vector<vector<int>*>* third  = new vector<vector<int>*>();
	third->push_back( CreateRow( _columns, 0, 1, 0, 0 ) );
	third->push_back( CreateRow( _columns, 1, 1, 1, 0 ) );
	third->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );
	third->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );

	vector<vector<int>*>* fourth = new vector<vector<int>*>();
	fourth->push_back( CreateRow( _columns, 1, 0, 0, 0 ) );
	fourth->push_back( CreateRow( _columns, 1, 1, 0, 0 ) );
	fourth->push_back( CreateRow( _columns, 1, 0, 0, 0 ) );
	fourth->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );

	_grid->push_back( first );

	_grid->push_back( second );

	_grid->push_back( third );

	_grid->push_back( fourth );

	first  = nullptr;

	second = nullptr;

	third  = nullptr;

	fourth = nullptr;


	_spriteURL = "assets/Gameplay/Tetromino/T.png";
}

TTetromino::~TTetromino(void)
{
}


