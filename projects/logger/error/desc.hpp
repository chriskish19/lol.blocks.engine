/***************************************
*  File: desc.hpp (description)
*
*  Purpose: error code messages
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include TYPES_INCLUDE_PATH

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
}