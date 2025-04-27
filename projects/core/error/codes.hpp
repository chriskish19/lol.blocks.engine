/***************************************
*  File: codes.hpp
*
*  Purpose: error codes
*
*
* *************************************/

#pragma once



namespace core {
	enum class codes {
		success = 0,
		uninitialized,
		register_class_fail,
		hwnd_error,
	};
}