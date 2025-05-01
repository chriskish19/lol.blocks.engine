#include NAMES_INCLUDE
#include ERROR_UTILS_INCLUDE_PATH

core::string core::match_code(codes code) {
	switch (code) {
		case codes::success:
			return success_description;
		case codes::uninitialized:
			return uninitialized_description;
		case codes::register_class_fail:
			return register_class_fail_description;
		case codes::hwnd_error:
			return hwnd_error_description;
		case codes::to_wide_string_failed:
			return to_wide_string_failed_description;
		case codes::to_narrow_string_failed:
			return to_narrow_string_failed_description;
		case codes::string_length_too_long:
			return string_length_too_long_description;
		default:
			return match_code_default_description;
	}
}

