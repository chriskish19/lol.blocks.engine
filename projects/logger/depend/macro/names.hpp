/***************************************
*  File: names.hpp
*
*  Purpose: easy file move/name changes without 
*			without breaking #include paths
*  
*  Project: logger
* 
*  INCLUDE NAME: LOGGER_NAMES
* *************************************/

// dependencies
#define LOGGER_STL_PRIVATE_INCLUDE_PATH				LOGGER_stl_includes_hpp					// the entire stl library
#define LOGGER_WIN_INCLUDE_PATH						LOGGER_win_hpp							// all windows includes
#define LOGGER_STL_INCLUDE_PATH						LOGGER_stl_hpp							// specific version include stl library
#define LOGGER_TYPES_INCLUDE_PATH					LOGGER_types_hpp						// handles unicode types and some macros
#define LOGGER_DEPENDS_INCLUDE_PATH					LOGGER_d_inc_hpp						// include all dependencies

// classes
#define LOGGER_FILE_INCLUDE_PATH					LOGGER_file_hpp							// logs to a file
#define LOGGER_WINDOW_LOGGER_INCLUDE_PATH			LOGGER_wl_hpp							// window logger terminal
#define LOGGER_BASE_INCLUDE_PATH					LOGGER_base_hpp							// base logger
#define LOGGER_MQSYS_INCLUDE_PATH					LOGGER_m_q_sys_hpp						// message queue system

// error
#define LOGGER_CODES_INCLUDE_PATH					LOGGER_codes_hpp						// error codes
#define LOGGER_DESC_INCLUDE_PATH					LOGGER_desc_hpp							// description of error codes
#define LOGGER_CO_INCLUDE_PATH						LOGGER_co_hpp							// code object

// log api
#define LOGGER_LOG_API_INCLUDE_PATH					LOGGER_log_api_hpp						// helper functions

// include all logs headers
#define LOGGER_ALL_LOGS_INCLUDE_PATH				LOGGER_all_logs_hpp						// includes all headers from logger project

// init
#define LOGGER_SYSINIT_INCLUDE_PATH					LOGGER_system_init_hpp					// functions for using the logger library