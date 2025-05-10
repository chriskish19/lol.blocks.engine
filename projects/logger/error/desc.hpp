/***************************************
*  File: desc.hpp (description)
*
*  Purpose: error code messages
*
*  Project: logger
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_TYPES_INCLUDE_PATH

namespace logger {
	inline const character* success_description = ROS("logger code: successful execution.");
	inline const character* uninitialized_description = ROS("logger code: code is uninitialized, means the core code enum was not explicitly initialized. Default setting.");
	inline const character* register_class_fail_description = ROS("logger code: attempted to register win32 window class but failed.");
	inline const character* hwnd_error_description = ROS("logger code: hwnd is nullptr.");
	inline const character* to_wide_string_failed_description = ROS("logger code: converting from narrow string to wide string has failed.");
	inline const character* get_client_rect_fail_description = ROS("logger code: the windows function GetClientRect() failed to retreive the client rect.");
	inline const character* module_handle_error_description = ROS("logger code: the module instance handle to the exe is nullptr.");
	inline const character* get_scroll_info_fail_description = ROS("logger code: the windows function GetScrollInfo() failed to retrive values.");
	inline const character* scroll_window_fail_description = ROS("logger code: the windows function ScrollWindow() failed to scroll the window.");
	inline const character* invalidate_rect_fail_description = ROS("logger code: the windows function InvalidateRect() failed to invalidate the window region for redraw.");
	inline const character* update_window_fail_description = ROS("logger code: the windows function UpdateWindow() failed to update the window.");
	inline const character* to_narrow_string_failed_description = ROS("logger code: converting from wide string to narrow has failed.");
	inline const character* hdc_error_description = ROS("logger code: handle to drawing context is nullptr.");
	inline const character* draw_text_error_description = ROS("logger code: the windows function DrawText() has failed to draw text to the window.");
	inline const character* write_to_file_error_description = ROS("attempting to write to a file has failed.");
	inline const character* file_open_error_description = ROS("failed to open file for reading or writing.");
	inline const character* font_nullptr_description = ROS("font handle is nullptr.");
	inline const character* get_text_metrics_fail_description = ROS("the windows function GetTextMetrics() failed to get the text settings.");
	inline const character* default_match_code_description = ROS("no matching code found (match_code function called).");
	inline const character* divison_by_zero_description = ROS("attempting to divide by zero results in undefined behavoir.");
}