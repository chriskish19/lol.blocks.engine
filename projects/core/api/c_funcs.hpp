/***************************************
*  File: c_funcs.hpp (core functions)
*
*  Purpose: helper functions
*
*  Project: core
* *************************************/

#pragma once
#include CORE_NAMES_INCLUDE
#include CORE_TYPES_INCLUDE_PATH
#include CORE_STL_INCLUDE_PATH
#include CORE_CODES_INCLUDE_PATH
#include CORE_CODE_OBJECT_INCLUDE_PATH

namespace core {
	// string conversions, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	// throws exception on error
	const size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const char* narrow);
	std::wstring to_wide_string(const std::string& narrow);
	std::string to_narrow_string(const wchar_t* wide);
	std::string to_narrow_string(const std::wstring& wide);

	// string conversions with error codes, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	std::wstring to_wide_string(const char* narrow, codes* code_p);
	std::wstring to_wide_string(const std::string& narrow, codes* code_p);
	std::string to_narrow_string(const wchar_t* wide, codes* code_p);
	std::string to_narrow_string(const std::wstring& wide, codes* code_p);
}