/***************************************
*  File: types.hpp
*
*  Purpose: handle settings
*
*  Project: logger
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_STL_INCLUDE_PATH
#include LOGGER_WIN_INCLUDE_PATH




#define MAX_STRING 512


#if defined(UNICODE) || defined(_UNICODE)

// macro for handling wide strings 
#define WIDE 1

// read only string, prepends L""
#define ROS(x) L##x

// cerr
#define CERROR std::wcerr

namespace logger {
	using string = std::wstring;
	using character = wchar_t;
	using character_p = character*;
	using const_character_p = const character*;
	using ofstream = std::wofstream;
	namespace fs = std::filesystem;
}

#else

#define ROS(x) x
#define NARROW 1

namespace logger {
	using string = std::string;
	using character = char;
}


#endif


#ifdef LOGS_EXPORTS
#define LOGS_API __declspec(dllexport)
#else
#define LOGS_API __declspec(dllimport)
#endif

// auto logger uses the system_log object for logging
#define AUTO_LOGGER 1

// manual logger uses basic functions for logging
#define MANUAL_LOGGER 0