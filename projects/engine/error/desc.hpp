/***************************************
*  File: desc.hpp (error code description)
*
*  Purpose: error code messages
*
*  Project: engine
* *************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE
#include ENGINE_TYPES_INCLUDE_PATH


namespace engine {
	inline const character* success_description = ROS("engine code: success | message: successful execution.");
	inline const character* uninitialized_description = ROS("engine code: uninitialized | message: code is uninitialized, means the core code enum was not explicitly initialized. Default setting.");
	inline const character* to_wide_string_failed_description = ROS("engine code: to_wide_string_failed | message: converting from narrow to wide string failed.");
	inline const character* to_narrow_string_failed_description = ROS("engine code: to_narrow_string_failed | message: converting from wide string to narrow has failed.");
	inline const character* default_match_code_description = ROS("engine code: default_match_code | message: no matching code found (match_code function called).");
	inline const character* pointer_is_nullptr_description = ROS("engine code: pointer_is_nullptr | message: pointer is'nt pointing to anything, no memory.");
	inline const character* dx_error_description = ROS("engine code: dx_error | message: direct x error.");
	inline const character* client_rect_fail_description = ROS("engine code: client_rect_fail | message: failed to get client rect.");
}