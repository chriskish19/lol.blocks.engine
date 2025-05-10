/***************************************
*  File: types.hpp 
*
*  Purpose: handle defined types and 
*           macros
*
*  Project: engine
* *************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
