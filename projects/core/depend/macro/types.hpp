/***************************************
*  File: types.hpp
*
*  Purpose: handle unicode within namespaces
*
*  Project: core
* *************************************/

#pragma once
#include CORE_NAMES_INCLUDE
#include CORE_STL_INCLUDE_PATH
#include CORE_WIN_INCLUDE_PATH




#define MAX_STRING 512

#if defined(UNICODE) || defined(_UNICODE)

// macro for handling wide strings 
#define WIDE 1

// read only string, prepends L""
#define ROS(x) L##x

#define COUT std::wcout
namespace core {
	using string = std::wstring;
	using character = wchar_t;
	using character_p = character*;
	using const_character_p = const character*;
}

#else

#define ROS(x) x
#define NARROW 1

namespace core {
	using string = std::string;
	using character = char;
}


#endif

// entry in main.cpp
#define MAIN_ENTRY 1
#define TEST_ENTRY 0

// terminal logging
#define CORE_SYS_LOG_OUT 1
#define CORE_STD_COUT 0
#define CORE_VS_OUT_WINDOW 0