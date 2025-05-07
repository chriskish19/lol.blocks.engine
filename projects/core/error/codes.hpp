/***************************************
*  File: codes.hpp
*
*  Purpose: error codes
*
*  Project: core
* *************************************/

#pragma once



namespace core {
	enum class codes {
		success = 0,
		uninitialized,
		register_class_fail,
		hwnd_error,
		to_wide_string_failed,
		to_narrow_string_failed,
		string_length_too_long,
		match_code_default,
		
	};
}