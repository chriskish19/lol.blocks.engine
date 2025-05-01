/***************************************
*  File: object.hpp (error object)
*
*  Purpose: a throwable error object
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include CODES_INCLUDE_PATH
#include CODE_DESC_INCLUDE_PATH
#include STL_INCLUDE_PATH


namespace core {
	// get location information
	string gl(std::source_location sl = std::source_location::current());

	// lol.blocks.error
	class lbe : public std::exception{
	public:
		lbe() = default;
		lbe(codes code, const string& desc, const string& location = gl() )
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