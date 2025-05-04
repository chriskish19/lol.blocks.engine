/***************************************
*  File: names.hpp
*
*  Purpose: easy file move/name changes without 
*			without breaking #include paths
*
* *************************************/

// dependencies
#define STL_PRIVATE_INCLUDE_PATH			stl_includes_hpp				// the entire stl library
#define WIN_INCLUDE_PATH					win_hpp							// all windows includes
#define STL_INCLUDE_PATH					stl_hpp							// specific version include stl library
#define TYPES_INCLUDE_PATH					types_hpp						// handles unicode types and some macros
#define DEPENDS_INCLUDE_PATH				d_inc_hpp						// include all dependencies

// classes
#define FILE_INCLUDE_PATH					file_hpp						// logs to a file
#define WINDOW_LOGGER_INCLUDE_PATH			wl_hpp							// window logger terminal
#define BASE_INCLUDE_PATH					base_hpp						// base logger

// error
#define CODES_INCLUDE_PATH					codes_hpp						// error codes
#define DESC_INCLUDE_PATH					desc_hpp						// description of error codes
#define CO_INCLUDE_PATH						co_hpp							// code object