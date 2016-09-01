#pragma once
#include "Tetromino.h"

class ZTetromino:public Tetromino
{
public:
	ZTetromino(IState* stateInstance);
	~ZTetromino(void);
};