/***************************************
*  File: types.hpp 
*
*  Purpose: handle defined types and 
*           macros
*
*  Project: engine
* *************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE

#define MAX_STRING 512

#if defined(UNICODE) || defined(_UNICODE)

// macro for handling wide strings 
#define WIDE 1

// read only string, prepends L""
#define ROS(x) L##x

namespace engine {
	using string = std::wstring;
	using character = wchar_t;
	using character_p = character*;
	using const_character_p = const character*;


	namespace dx11 {
		using string = engine::string;
		using character = engine::character;
		using character_p = engine::character*;
		using const_character_p = const engine::character*;
	}
}


#else

#define ROS(x) x
#define NARROW 1

namespace engine {
	using string = std::string;
	using character = char;
}


#endif

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
