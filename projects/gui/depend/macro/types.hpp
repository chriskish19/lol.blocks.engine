/***************************************
*  File:
*
*  Purpose:
*
*
* *************************************/

#pragma once
#include GUI_NAMES_INCLUDE

#ifdef GUI_EXPORTS
#define GUI_API __declspec(dllexport)
#else
#define GUI_API __declspec(dllimport)
#endif