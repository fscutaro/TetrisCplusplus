#pragma once
#include "Tetromino.h"

class LTetromino:public Tetromino
{
public:
	LTetromino(IState* stateInstance);
	~LTetromino(void);
};