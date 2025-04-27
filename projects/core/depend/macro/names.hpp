/***************************************
*  File: names.hpp
*
*  Purpose: easy file move/name changes without 
*			without breaking #include paths
*
* *************************************/

#define STL_PRIVATE_INCLUDE_PATH			stl_includes_hpp				// the entire stl library
#define WIN_INCLUDE_PATH					win_hpp							// all windows includes
#define STL_INCLUDE_PATH					stl_hpp							// specific version include stl library
#define ALL_CORE_INCLUDE_PATH				all_core_hpp					// all header includes in core project
#define TYPES_INCLUDE_PATH					types_hpp						// handles unicode types and some macros
#define CODE_DESC_INCLUDE_PATH				desc_hpp						// (code description) has error code descriptions as strings
#define CORE_WINDOW_INCLUDE_PATH			c_window_hpp					// win32 window class
#define CODES_INCLUDE_PATH					codes_hpp						// error codes