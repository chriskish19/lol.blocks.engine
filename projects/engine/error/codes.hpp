/***************************************
*  File: codes.hpp (engine error codes)
*
*  Purpose: define engine error codes
*
*  Project: engine
* *************************************/

#pragma once

namespace engine {
	enum class codes {
		success = 0,
		uninitialized,
		to_wide_string_failed,
		to_narrow_string_failed,
		default_match_code,
		pointer_is_nullptr,
		dx_error,
		client_rect_fail,

	};
}