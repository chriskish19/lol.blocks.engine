/***************************************
*  File: eu.hpp (error utilities)
*
*  Purpose: provide helper functions
*			for error related problems
*  
*  Project: core
* *************************************/

#pragma once
#include CORE_NAMES_INCLUDE
#include CORE_TYPES_INCLUDE_PATH
#include CORE_CODES_INCLUDE_PATH
#include CORE_CODE_DESC_INCLUDE_PATH
#include CORE_CODE_OBJECT_INCLUDE_PATH


// logger library
#include LOGGER_NAMES_INCLUDE
#include LOGGER_ALL_LOGS_INCLUDE_PATH


namespace core {
	// match a code to an error description
	string match_code(codes code);

	// outputs a message to the terminal
	// controlled by macros where the message is routed to
	// under (.../depends/macros/types.hpp)
	void output_code(codes code,const string& location = core::gl());

	// outputs a core error to the terminal
	// controlled by macros where the message is routed to
	// under (.../depends/macros/types.hpp)
	void output_co(const core::ce& e);
}