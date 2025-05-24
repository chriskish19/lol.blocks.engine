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
	inline const character* success_description = ROS("logger code: success | message: successful execution.");
	inline const character* uninitialized_description = ROS("logger code: uninitialized | message: code is uninitialized, means the core code enum was not explicitly initialized. Default setting.");
	inline const character* register_class_fail_description = ROS("logger code: register_class_fail | message: attempted to register win32 window class but failed.");
	inline const character* hwnd_error_description = ROS("logger code: hwnd_error | message: hwnd is nullptr.");
	inline const character* to_wide_string_failed_description = ROS("logger code: to_wide_string_failed | message: converting from narrow string to wide string has failed.");
	inline const character* get_client_rect_fail_description = ROS("logger code: get_client_rect_fail | message: the windows function GetClientRect() failed to retreive the client rect.");
	inline const character* module_handle_error_description = ROS("logger code: module_handle_error | message: the module instance handle to the exe is nullptr.");
	inline const character* get_scroll_info_fail_description = ROS("logger code: get_scroll_info_fail | message: the windows function GetScrollInfo() failed to retrive values.");
	inline const character* scroll_window_fail_description = ROS("logger code: scroll_window_fail | message: the windows function ScrollWindow() failed to scroll the window.");
	inline const character* invalidate_rect_fail_description = ROS("logger code: invalidate_rect_fail | message: the windows function InvalidateRect() failed to invalidate the window region for redraw.");
	inline const character* update_window_fail_description = ROS("logger code: update_window_fail | message: the windows function UpdateWindow() failed to update the window.");
	inline const character* to_narrow_string_failed_description = ROS("logger code: to_narrow_string_failed | message: converting from wide string to narrow has failed.");
	inline const character* hdc_error_description = ROS("logger code: hdc_error | message: handle to drawing context is nullptr.");
	inline const character* draw_text_error_description = ROS("logger code: draw_text_error | message: the windows function DrawText() has failed to draw text to the window.");
	inline const character* write_to_file_error_description = ROS("logger code: write_to_file_error | message: attempting to write to a file has failed.");
	inline const character* file_open_error_description = ROS("logger code: file_open_error | message: failed to open file for reading or writing.");
	inline const character* font_nullptr_description = ROS("logger code: font_nullptr | message: font handle is nullptr.");
	inline const character* get_text_metrics_fail_description = ROS("logger code: get_text_metrics_fail | message: the windows function GetTextMetrics() failed to get the text settings.");
	inline const character* default_match_code_description = ROS("logger code: default_match_code | message: no matching code found (match_code function called).");
	inline const character* divison_by_zero_description = ROS("logger code: divison_by_zero | message: attempting to divide by zero results in undefined behavoir.");
	inline const character* logger_exception_caught_description = ROS("logger code: logger_exception_caught | message: a logger exception was thrown and caught.");
	inline const character* unknown_exception_caught_description = ROS("logger code: unknown_exception_caught | message: an unknown exception was thrown and caught.");
	inline const character* pointer_is_nullptr_description = ROS("logger code: pointer_is_nullptr | message: pointer has no memory to point to.");
	inline const character* index_out_of_range_description = ROS("logger code: index_out_of_range | message: index is beyond the size of the container.");
}