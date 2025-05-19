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
    class system_log {
    public:
        system_log();
        ~system_log();

        // Overload operator<< to log messages to log_terminal
        template <typename T>
        system_log& operator<<(const T& value) {
            if (log_terminal) {
                
#if WIDE
                std::wostringstream oss;
                oss << value;
                log_terminal->send_message(oss.str());
#else
                std::ostringstream oss;
                oss << value;
                log_terminal->send_message(oss.str());
#endif
            }
            return *this;
        }

        void log_message(const string& message) {
            log_terminal->send_message(message);
        }

        logger::classic_log_window* get_terminal_p() { return log_terminal; }
    protected:
        logger::classic_log_window* log_terminal = nullptr;
        std::thread* lt_thread = nullptr;
    };

    // global system logger object
    extern LOGS_API std::unique_ptr<system_log> glb_sl;

#endif
}