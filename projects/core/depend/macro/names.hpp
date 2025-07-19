/***************************************
*  File: names.hpp
*
*  Purpose: easy file move/name changes without 
*			without breaking #include paths
* 
*  Project: core
* *************************************/

// dependencies
#define CORE_STL_PRIVATE_INCLUDE_PATH			CORE_stl_includes_hpp				// the entire stl library
#define CORE_WIN_INCLUDE_PATH					CORE_win_hpp						// all windows includes
#define CORE_STL_INCLUDE_PATH					CORE_stl_hpp						// specific version include stl library
#define CORE_TYPES_INCLUDE_PATH					CORE_types_hpp						// handles unicode types and some macros
#define CORE_DEPENDS_INCLUDE_PATH				CORE_d_inc_hpp						// all dependencies

// includes entire core
#define CORE_ALL_CORE_INCLUDE_PATH				CORE_all_core_hpp					// all header includes in core project

// classes
#define CORE_WINDOW_INCLUDE_PATH				CORE_c_window_hpp					// win32 window class

// api helper functions
#define CORE_FUNCTIONS_INCLUDE_PATH				CORE_core_funcs_hpp					// helper functions

// error
#define CORE_CODES_INCLUDE_PATH					CORE_codes_hpp						// error codes
#define CORE_CODE_OBJECT_INCLUDE_PATH			CORE_object_hpp						// throwable error object 
#define CORE_ERROR_UTILS_INCLUDE_PATH			CORE_eu_hpp							// error utilities helper functions
#define CORE_CODE_DESC_INCLUDE_PATH				CORE_desc_hpp						// (code description) has error code descriptions as strings