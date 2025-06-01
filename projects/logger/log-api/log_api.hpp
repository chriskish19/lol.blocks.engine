/***************************************
*  File: log_api.hpp 
*
*  Purpose: helper functions
*
*  Project: logger
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_CO_INCLUDE_PATH
#include LOGGER_BASE_INCLUDE_PATH


namespace logger{
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


	// simple time stamp a message
	// returns the message with a time on it ([2025-05-09-14:00:30...])
	string time_stamped(const string& message);

	// log a CO object to the terminal
	void er_co_out(codes code);
}