#pragma once
#include "Tetromino.h"

class JTetromino:public Tetromino
{
public:
	JTetromino(IState* stateInstance);
	~JTetromino(void);
};