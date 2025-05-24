/***************************************
*  File: eu.cpp (error utilities)
*
*  Purpose: error utilities definitions
*
*  Project: core
* *************************************/


#include CORE_NAMES_INCLUDE
#include CORE_ERROR_UTILS_INCLUDE_PATH

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
		case codes::get_client_rect_fail:
			return get_client_rect_fail_description;
		case codes::unknown_exception_caught:
			return unknown_exception_caught_description;
		case codes::std_exception_caught:
			return std_exception_caught_description;
		default:
			return match_code_default_description;
	}
}

void core::output_code(codes code, const string& location)
{
	logger::string message = core::match_code(code);
#if CORE_SYS_LOG_OUT
	logger::glb_sl->log_message(message + ROS('\n') + ROS("LOCATION: ") + location);
#endif
#if CORE_STD_COUT
	COUT << message << '\n' << ROS("LOCATION: ") << location;
#endif
#if CORE_VS_OUT_WINDOW
	message = message + "\n" + location;
	OutputDebugString(message.c_str());
#endif

}

void core::output_co(const core::ce& e)
{
#if CORE_SYS_LOG_OUT
	logger::glb_sl->log_message(e.m_desc + ROS('\n') + ROS("LOCATION: ") + e.m_loc + ROS('\n') + ROS("WIN32 ERROR: ") + e.m_w32);
#endif
#if CORE_STD_COUT
	COUT << e.m_desc << '\n' << ROS("LOCATION: ") << e.m_loc << '\n' << ROS("WIN32 ERROR: ") << e.m_w32;
#endif
#if CORE_VS_OUT_WINDOW
	string message;
	message = e.m_desc + ROS('\n') + ROS("LOCATION: ") + e.m_loc + ROS('\n') + ROS("WIN32 ERROR: ") + e.m_w32;
	OutputDebugString(message.c_str());
#endif

}
