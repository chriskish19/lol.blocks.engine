/***************************************
*  File: codes.hpp (error codes)
*
*  Purpose: house error codes
*
*  Project: logger
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
		get_client_rect_fail,
		module_handle_error,
		get_scroll_info_fail,
		scroll_window_fail,
		invalidate_rect_fail,
		update_window_fail,
		to_narrow_string_failed,
		hdc_error,
	};
}