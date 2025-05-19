/***************************************
*  File: engine_api.hpp
*
*  Purpose: helper functions
*
*  Project: engine
* *************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_DEPENDS_INCLUDE_PATH
#include ENGINE_CO_INCLUDE_PATH



namespace engine {
	// string conversions, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	// throws exception on error
	// {
	const size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const char* narrow);
	std::wstring to_wide_string(const std::string& narrow);
	std::string to_narrow_string(const wchar_t* wide);
	std::string to_narrow_string(const std::wstring& wide);
	// }


	// string conversions with error codes, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	// {
	std::wstring to_wide_string(const char* narrow, codes* code_p);
	std::wstring to_wide_string(const std::string& narrow, codes* code_p);
	std::string to_narrow_string(const wchar_t* wide, codes* code_p);
	std::string to_narrow_string(const std::wstring& wide, codes* code_p);
	// }

	// gets the location of the caller function
	string gl(std::source_location sl = std::source_location::current());

	// outputs the code message
	void output_code(codes code,const string& location = gl());

	// matches a code to a description
	string match_code(codes code);
}