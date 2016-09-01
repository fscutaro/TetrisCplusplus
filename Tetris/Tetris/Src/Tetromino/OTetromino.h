#pragma once
#include "Tetromino.h"

class OTetromino:public Tetromino
{
public:
	OTetromino(IState* stateInstance);
	~OTetromino(void);
};