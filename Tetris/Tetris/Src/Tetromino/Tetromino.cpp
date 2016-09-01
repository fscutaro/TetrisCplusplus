#include "Tetromino.h"
#include "../../Core/Constants.h"
#include <iostream>
#include <stdarg.h>

Tetromino::Tetromino( IState* stateInstance )
{
	tileX			 = 0;
	tileY		     = 0;
	_parentInstance  = stateInstance; 
	_graphics		 = new std::vector<Sprite*>();
	_currentRotation = 0;
	_columns		 = 4;
	_rows			 = 4;
}

Tetromino::~Tetromino(void)
{
	Clear();
	_graphics->clear();
	SAFE_DELETE_OBJECT(_graphics);
	_graphics		= nullptr;

	for( int i = 0; i < _rows; i++ )
	{
		_grid->at( _currentRotation )->at(i)->clear();
		SAFE_DELETE_OBJECT(_grid->at( _currentRotation )->at(i));
	}

	_grid->at( _currentRotation )->clear();
	SAFE_DELETE_OBJECT(_grid);
	_grid			= nullptr;
	_parentInstance = nullptr;
}


vector<int>* Tetromino::CreateRow( int amount, ... )
{
	vector<int>* vec = new vector<int>();

	va_list ap;
    int i;
    va_start(ap, amount);
    for(i=0; i<amount; i++)
		vec->push_back( va_arg(ap, int) );
    va_end(ap);

	return vec;
}

void Tetromino::Draw()
{
	Sprite* t;
	for( int i = 0; i < _rows; i++ )
	{
		for( int j = 0; j < _columns; j++ )
		{
			if( _grid->at( _currentRotation )->at(i)->at(j) == 1 )
			{
				t = new Sprite(_spriteURL );
				_parentInstance->addChild( t );
				t->x = ( j *  t->getWidth()  ) + _x;
				t->y = ( i *  t->getHeight() ) + _y;
				_graphics->push_back( t );
			}
		}
	}
	t = nullptr;
}

void Tetromino::Rotate()
{
	_currentRotation++;
	if( _currentRotation == _maxRotations )
	{
		_currentRotation = 0;
	}

	SetPos(_x, _y);
}

void Tetromino::Clear()
{
	for( int i = 0; i < _graphics->size(); i++ )
	{
		_parentInstance->removeChild( _graphics->at(i) );
	}
}

void Tetromino::SetPos(float x, float y)
{
	_x = x;
	_y = y;

	int currentItem = 0;
	Sprite* t;
	for( int i = 0; i < _rows; i++ )
	{
		for( int j = 0; j < _columns; j++ )
		{
			if( _grid->at( _currentRotation )->at(i)->at(j) == 1 )
			{
				t = _graphics->at( currentItem );
				t->x = ( j *  t->getWidth() )  + _x;
				t->y = ( i *  t->getHeight() ) + _y;
				currentItem++;
			}
		}
	}
	t = nullptr;
}

float Tetromino::GetX()
{
	return _x;
}

float Tetromino::GetY()
{
	return _y;
}

std::vector< std::vector<int>* >* Tetromino::GetGrid()
{
	return _grid->at( _currentRotation );
}

std::vector< std::vector<int>* >* Tetromino::GetNextRotation()
{
	int nextRotation = _currentRotation + 1;
	if( nextRotation == _maxRotations )
	{
		nextRotation = 0;
	}

	return _grid->at( nextRotation );
}

char* Tetromino::getSpriteURL()
{
	return _spriteURL;
}
