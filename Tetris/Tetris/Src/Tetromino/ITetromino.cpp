#include "ITetromino.h"
#include <vector>
#include "../../Core/FSM/IState.h"

using namespace std;
ITetromino::ITetromino(IState* stateInstance):Tetromino(stateInstance)
{
	_maxRotations = 2;

	_grid = new vector<vector<vector<int>*>*>();

	vector<vector<int>*>* first = new vector<vector<int>*>();
	first->push_back( CreateRow( _columns, 0, 0, 1, 0 ) );
	first->push_back( CreateRow( _columns, 0, 0, 1, 0 ) );
	first->push_back( CreateRow( _columns, 0, 0, 1, 0 ) );
	first->push_back( CreateRow( _columns, 0, 0, 1, 0 ) );

	vector<vector<int>*>* second = new vector<vector<int>*>();
	second->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );
	second->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );
	second->push_back( CreateRow( _columns, 1, 1, 1, 1 ) );
	second->push_back( CreateRow( _columns, 0, 0, 0, 0 ) );

	_grid->push_back( first );

	_grid->push_back( second );

	first  = nullptr;

	second = nullptr;

	_spriteURL = "assets/Gameplay/Tetromino/I.png";
}

ITetromino::~ITetromino(void)
{
}


