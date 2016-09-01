#pragma once
#include "Tetromino.h"

class TTetromino:public Tetromino
{
public:
	TTetromino(IState* stateInstance);
	~TTetromino(void);
};