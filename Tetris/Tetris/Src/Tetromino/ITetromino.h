#pragma once
#include "Tetromino.h"

class ITetromino:public Tetromino
{
public:
	ITetromino(IState* stateInstance);
	~ITetromino(void);
};