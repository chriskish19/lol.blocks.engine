/***************************************
*  File: desc.hpp (description of error code)
*
*  Purpose: list of strings containing 
*			descriptions of codes
*  
*  Project: core
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include TYPES_INCLUDE_PATH

namespace core {
	inline const character* success_description = ROS("core code: successful execution.");
	inline const character* uninitialized_description = ROS("core code: code is uninitialized, means the core code enum was not explicitly initialized. Default setting.");
	inline const character* register_class_fail_description = ROS("core code: attempted to register win32 window class but failed.");
	inline const character* hwnd_error_description = ROS("core code: hwnd is nullptr.");
	inline const character* to_wide_string_failed_description = ROS("core code: converting from narrow string to wide string has failed.");
	inline const character* to_narrow_string_failed_description = ROS("core code: converting from wide string to narrow has failed.");
	inline const character* string_length_too_long_description = ROS("core code: string length exceeds avaliable memory or predefined limit.");
	inline const character* match_code_default_description = ROS("core code: unable to match code");

}