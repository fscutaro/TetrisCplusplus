#pragma once
#include "Tetromino.h"

class STetromino:public Tetromino
{
public:
	STetromino(IState* stateInstance);
	~STetromino(void);
};