#pragma once
#include "IInputController.h"
#include "../Events/EventDispatcher.h"

class InputController:IInputController,public EventDispatcher
{
};