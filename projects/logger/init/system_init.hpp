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
#include LOGGER_MQSYS_INCLUDE_PATH


namespace logger {
#if MANUAL_LOGGER
	extern LOGS_API logger::classic_log_window* log_terminal;
	extern LOGS_API std::thread* lt_thread;

	// initialize the logger system
	codes LOGS_API init_system_log();

	void LOGS_API log_message(const string& message);

	// exit the logger system
	// make sure to call this if you call init_system_log()
	codes LOGS_API exit_system_log();
#else

    // use this class instead of functions
    class LOGS_API system_log : public classic_log_window{
    public:
        system_log();
        ~system_log();

        void log_message(const string& message);
    };

    // global system logger object
    extern LOGS_API std::unique_ptr<system_log> glb_sl;

#endif
}