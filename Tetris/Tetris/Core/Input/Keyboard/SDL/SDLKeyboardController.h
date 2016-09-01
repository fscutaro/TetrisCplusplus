#pragma once
#include "../../InputController.h"
class KeyboardController:InputController
{
public:
	KeyboardController(void);
	~KeyboardController(void);
	void Update();
	void OnEventHandled(const char* name);
};