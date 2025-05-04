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
	inline const character* success_description = ROS("core code: successful execution.");
	inline const character* uninitialized_description = ROS("core code: code is uninitialized, means the core code enum was not explicitly initialized. Default setting.");
	inline const character* register_class_fail_description = ROS("core code: attempted to register win32 window class but failed.");
	inline const character* hwnd_error_description = ROS("core code: hwnd is nullptr.");
}