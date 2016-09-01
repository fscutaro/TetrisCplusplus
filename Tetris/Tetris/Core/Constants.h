#pragma once

#define USE_SDL
#include <iostream>
#ifdef USE_SDL
#define WINDOW_ID 1
#endif

#define SAFE_DELETE_OBJECT( obj ) if( obj != nullptr ){ delete obj; obj = nullptr; }

#define SAFE_DELETE_ARRAY( arr ) if( arr != nullptr ){ delete[] arr; arr = nullptr;  }