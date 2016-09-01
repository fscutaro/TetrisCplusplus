#include "Board.h"
#include "../../Core/Constants.h"
#include "../Tetromino/Tetromino.h"
#include <vector>
#include "../../Core/FSM/IState.h"
#include "../../Core/Display/Sprite.h"

const int Board::ROWS    = 20;
const int Board::COLUMNS = 10;

using namespace std;
Board::Board(IState* parentState)
{

	_parentState = parentState;

	_placedeTetrominoesGraphics = new vector<Sprite*>();

	int grid[20][10] = 
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	};

	_grid = new vector<vector<int>*>();

	for	( int i = 0 ; i < ROWS; i++ )
	{
		_grid->push_back( new vector<int>() );
		for( int j = 0; j < COLUMNS; j++ )
		{
			_grid->at(i)->push_back( grid[i][j] );
		}
	}
}

vector<vector<int>*>* Board::getGrid()
{
	return _grid;
}

Board::~Board(void)
{
	_parentState = nullptr;
	_placedeTetrominoesGraphics->clear();
	SAFE_DELETE_OBJECT( _placedeTetrominoesGraphics );
	
	for( int i = 0; i < ROWS; i++ )
	{
		_grid->at(i)->clear();
	}

	_grid->clear();
	SAFE_DELETE_OBJECT( _grid );
}

bool Board::tetrominoIsGrounded(Tetromino* t)
{
	std::vector< std::vector<int>* >* grid = t->GetGrid();

	std::vector<int>* currentFloor;
	int currentFlorSize = 0;

	int numRows	   = grid->size() - 1;
	int numColumns = grid->at(0)->size() - 1;
	int floorValue = 0;
	int floorY	   = 0;
	int floorX	   = 0;

	for( int i = numRows; i >= 0 ; i-- )
	{
		currentFloor	= grid->at( i );
		currentFlorSize = currentFloor->size();
		for( int j = currentFlorSize - 1; j >= 0 ; j-- )
		{
			floorValue = currentFloor->at( j );
			if( floorValue == 1 )
			{
				floorY = t->tileY + i;
				floorX = t->tileX + j;
				//The tetromino just hitted the floor
				if( floorY == ( ROWS - 1 ) )
				{
					return true;
				}
				if( floorX < COLUMNS )
				{
					//The tetromino just hitted another tetromino
					if( _grid->at( floorY + 1 )->at( floorX ) == 1 )
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Board::canRotate( Tetromino* t )
{
	return _fitsInGrid(t, t->GetNextRotation(), 0 );
}

bool Board::canMove( Tetromino* t, int direction )
{
	return _fitsInGrid(t, t->GetGrid(), direction );
}

bool Board::_fitsInGrid( Tetromino* t, std::vector< std::vector<int>* >* grid, int direction)
{
	int numRows	   = grid->size() - 1;
	int numColumns = grid->at(0)->size() - 1;
	int floorValue = 0;
	int floorY	   = 0;
	int floorX	   = 0;
	int tileXRight = 0;

	for	( int i = 0; i < numRows; i++ )
	{
		for( int j = 0; j < numColumns; j++ )
		{
			if( grid->at( i )->at( j ) == 1 )
			{
				if( tileXRight < j )
				{
					tileXRight = j;
				}
				//std::cout<<"tileXRight = "<<tileXRight<<"\n";
			}
		}
	}

	//check collision with left wall
	if( t->tileX <= 0 && direction < 0 )
	{
		std::cout<<"t->tileX == 0 = \n";
		return false;
	}

	//check collision with right wall
	if( ( t->tileX + tileXRight ) >= COLUMNS - 1 && direction > 0  )
	{
		std::cout<<" tileXRight == COLUMNS "<<( t->tileX + tileXRight ) <<"  \n";
		return false;
	}

	for	( int i = numRows; i >= 0 ; i-- )
	{
		for( int j = numColumns; j >= 0 ; j-- )
		{
			int y = t->tileY + i;
			int x = t->tileX + j + direction;
			if( x >= 0 && y < ROWS )
			{
				if( grid->at( i )->at( j ) == 1 )
				{
					if ( _grid->at( y )->at( x ) == 1 )
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}

//TODO: draw placed tetromino
void Board::placeTetromino( Tetromino* t )
{
	printBoard();

	int tileX = t->tileX ;
	int tileY = t->tileY;

	vector<vector<int>*>* grid = t->GetGrid();
	int gridRows	= tileY + ( grid->size() );
	int gridColumns = tileX +  ( grid->at(0)->size() );

	for( int i = tileY; i < gridRows  ; i++ )
	{
		//std::cout<<"i "<<i<<std::endl;
		for( int j = tileX; j < gridColumns; j++ )
		{
			if( grid->at( i - tileY )->at( j - tileX ) == 1 )
			{
				_grid->at( i )->at( j ) = 1;
			}
		}
	}
	printBoard();
}

//DEBUG ONLY
void Board::printBoard()
{
	std::cout<<std::endl;
	std::cout<<"Board::printBoard() "<<std::endl;
	for( int i = 0; i < _grid->size() ; i++ )
	{
		std::cout<<std::endl;
		for( int j = 0; j < _grid->at(i)->size(); j++ )
		{
			std::cout<<"-"<<_grid->at( i )->at( j );
		}
	}
}
