/***************************************
*  File: win.hpp (windows header includes)
* 
*  Purpose: include all relavent windows headers
*			in one convenient location 
* 
*  Project: logger
* *************************************/

#pragma once

// main windows header
#include <Windows.h>

// Undefine Windows macros to avoid conflicts
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif
