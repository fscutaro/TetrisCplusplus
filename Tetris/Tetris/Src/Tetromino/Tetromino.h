#pragma once
#include "../../Core/FSM/IState.h"
#include <vector>
using namespace std;
class Tetromino
{
public:
	Tetromino(IState* stateInstance);
	~Tetromino(void);
	void Draw();
	void Clear();
	void SetPos(float x, float y);
	float GetX();
	float GetY();
	float tileX;
	float tileY;
	std::vector< std::vector<int>* >* GetGrid();
	std::vector< std::vector<int>* >* GetNextRotation();
	void Rotate();
	char* getSpriteURL();
protected:
	int _columns;
	int _rows;
	int _maxRotations;
	char* _spriteURL;
	vector< vector< vector< int >* >* >* _grid;
	vector<int>* CreateRow( int amount, ... );
	vector< Sprite* >* _graphics;
	IState* _parentInstance;
	float _x;
	float _y;
	int _currentRotation;
};

