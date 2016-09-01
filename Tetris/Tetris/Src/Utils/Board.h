#pragma once
#include <vector>
#include "../Tetromino/Tetromino.h"
#include "../../Core/FSM/IState.h"
#include "../../Core/Display/Sprite.h"

using namespace std;
class Board
{
public:
	Board(IState* parentState );
	~Board(void);
	vector<vector<int>*>* getGrid();
	static const int COLUMNS;
	static const int ROWS   ;
	bool tetrominoIsGrounded(Tetromino* t);
	bool canRotate( Tetromino* t );
	bool canMove(Tetromino* t, int direction);
	void placeTetromino( Tetromino* t );
	void printBoard();
private:
	bool _fitsInGrid( Tetromino* t, std::vector< std::vector<int>* >* grid, int direction);
	vector<vector<int>*>* _grid;
	vector<Sprite*>* _placedeTetrominoesGraphics;
	IState* _parentState;
};

