#pragma once
#include "Core\Game.h"
class Tetris :
	public Game
{
public:
	Tetris( std::vector<IState*>* states );
	~Tetris(void);
};

