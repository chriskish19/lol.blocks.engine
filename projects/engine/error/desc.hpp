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
	inline const character* success_description = ROS("engine code: successful execution.");
	inline const character* uninitialized_description = ROS("engine code: code is uninitialized, means the core code enum was not explicitly initialized. Default setting.");
	inline const character* to_wide_string_failed_description = ROS("engine code: converting from narrow to wide string failed.");
	inline const character* to_narrow_string_failed_description = ROS("engine code: converting from wide string to narrow has failed.");
	inline const character* default_match_code_description = ROS("engine code: no matching code found (match_code function called).");
	inline const character* pointer_is_nullptr_description = ROS("engine code: pointer is'nt pointing to anything, no memory.");
}