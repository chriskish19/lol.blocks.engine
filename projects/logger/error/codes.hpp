/***************************************
*  File: codes.hpp (error codes)
*
*  Purpose: house error codes
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE

namespace logger {
	enum class codes {
		success=0,
		uninitialized,
		register_class_fail,
		hwnd_error,
		to_wide_string_failed,
		get_client_rect_fail
	};
}