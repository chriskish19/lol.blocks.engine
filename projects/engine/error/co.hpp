/***************************************
*  File: co.hpp (code object)
*
*  Purpose: throwable error objects
*
*  Project: engine
* *************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_DEPENDS_INCLUDE_PATH
#include ENGINE_CODES_INCLUDE_PATH
#include ENGINE_CD_INCLUDE_PATH



namespace engine {
	// get location information
	string ee_gl(std::source_location sl = std::source_location::current());
	
	// helper to convert to wide string
	std::wstring ee_to_wide(const std::string& narrow);

	// engine error
	class ee : public std::exception{
	public:
		ee() = default;
		ee(codes code, const string& desc, const string& location = ee_gl())
			: m_code(code), m_desc(desc), m_loc(location) {
		}

		// defaults init
		const codes m_code;
		const string m_desc;
		const string m_loc;
	};
}