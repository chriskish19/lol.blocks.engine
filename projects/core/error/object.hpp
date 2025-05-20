/***************************************
*  File: object.hpp (error object)
*
*  Purpose: a throwable error object
*
*  Project: core
* *************************************/

#pragma once
#include CORE_NAMES_INCLUDE
#include CORE_CODES_INCLUDE_PATH
#include CORE_CODE_DESC_INCLUDE_PATH
#include CORE_STL_INCLUDE_PATH


namespace core {
	// get location information
	string gl(std::source_location sl = std::source_location::current());

	// core error
	class ce : public std::exception{
	public:
		ce() = default;
		ce(codes code, const string& desc, const string& location = gl() )
			: m_code(code), m_desc(desc), m_loc(location) { }


		// defaults init
		const codes m_code;
		const string m_desc;
		const string m_loc;

		// helper to convert to wide string
		// cant use api, since api depends on this throwable object for error handling
		static std::wstring to_wide(const std::string& narrow);
	};
}