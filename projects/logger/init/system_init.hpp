/***************************************
*  File: system_init.hpp (system initialize)
*
*  Purpose: initilizes the logger library
*			and provides functions for 
*			using it
*
*  Project: logger
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_CODES_INCLUDE_PATH
#include LOGGER_WINDOW_LOGGER_INCLUDE_PATH



namespace logger {
	logger::classic_log_window* log_terminal = nullptr;
	std::thread* lt_thread = nullptr;

	// initialize the logger system
	codes init_system_log();

	void log_message(const string& message);

	// exit the logger system
	codes exit_system_log();
}