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

#define LOG_FLUSH 1000
#define LOG_OUT 1
#define LOG_FLUSH_TIME 5 // in milliseconds



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
    class LOGS_API system_log {
    public:
        system_log();
        ~system_log();

        void log_message(const string& message) {
            // get current log
            logger::log* log_p = m_logp_v.at(at_index());
            *log_p->message = message;
            m_lq->add_message(log_p);

            if (m_index % LOG_OUT == 0) {
                // signal queue to process message after timer is finished
                static auto last_flush = std::chrono::steady_clock::now();
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_flush).count() >= LOG_FLUSH_TIME) {
                    system_log_flush();
                    last_flush = now;
                }
            }
        }

        logger::classic_log_window* get_terminal_p() { return log_terminal; }
    protected:

        void system_log_flush();

        void alloc_new_logs();

        void dealloc_logs();

        std::size_t at_index();


        logger::classic_log_window* log_terminal = nullptr;
        logger::log_q* m_lq = nullptr;
        std::thread* m_qsys_thread = nullptr;

        std::size_t m_index = 0;

        std::vector<log*> m_logp_v;

        std::atomic<bool> m_all_logs_aloc = false;
    };

    // global system logger object
    extern LOGS_API std::unique_ptr<system_log> glb_sl;

#endif
}