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
#define TYPES_INCLUDE_PATH					types_hpp						// handles unicode types and some macros
#define FILE_INCLUDE_PATH					file_hpp						// logs to a file
#define DEPENDS_INCLUDE_PATH				d_inc_hpp						// include all dependencies