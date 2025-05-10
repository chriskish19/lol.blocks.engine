/***************************************
*  File: co.hpp (code object)
*
*  Purpose: a throwable object for 
*			exceptions and errors
*
*  Project: logger 
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_CODES_INCLUDE_PATH
#include LOGGER_DESC_INCLUDE_PATH



namespace logger {
	// get location information
	string gl(std::source_location sl = std::source_location::current());

	// logger error
	class le : public std::exception {
	public:
		le() = default;
		le(codes code, const string& desc, const string& location = gl(),const string& windows_error=get_w32_error())
			: m_code(code), m_desc(desc), m_loc(location),m_w32(windows_error) {
		}


		// defaults init
		const codes m_code;
		const string m_desc;
		const string m_loc;
		const string m_w32;

		// helper to convert to wide string
		static std::wstring to_wide(const std::string& narrow);

		// win32 error info
		static string get_w32_error();

		// match a code to its error description
		static string match_code(codes code);
	};
}