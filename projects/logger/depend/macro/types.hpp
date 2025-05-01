/***************************************
*  File: types.hpp
*
*  Purpose: handle settings
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include STL_INCLUDE_PATH
#include WIN_INCLUDE_PATH




#define MAX_STRING 512

#if defined(UNICODE) || defined(_UNICODE)

// macro for handling wide strings 
#define WIDE 1

// read only string, prepends L""
#define ROS(x) L##x

namespace logger {
	using string = std::wstring;
	using character = wchar_t;
	using character_p = character*;
	using const_character_p = const character*;
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