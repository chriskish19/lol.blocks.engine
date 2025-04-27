/***************************************
*  File: types.hpp
*
*  Purpose: handle unicode within namespaces
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include STL_INCLUDE_PATH
#include WIN_INCLUDE_PATH

#if defined(UNICODE) || defined(_UNICODE)

// macro for handling wide strings 
#define WIDE 1

// read only string, prepends L""
#define ROS(x) L##x

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