/***************************************
*  File: types.hpp
*
*  Purpose: handle types (unicode ect...)
*
*  Project: tests
* *************************************/

#pragma once
#include TEST_NAMES_INCLUDE
#include TEST_STL_INCLUDE_PATH



#if defined(UNICODE) || defined(_UNICODE)

// macro for handling wide strings 
#define WIDE 1

// read only string, prepends L""
#define ROS(x) L##x

// cerr
#define CERROR std::wcerr

namespace test {
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

#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif
