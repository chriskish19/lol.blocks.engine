/***************************************
*  File: m_q_sys.hpp (message queue system)
*
*  Purpose: buffer messages for the logger
*
*  Project: logger
* 
*  INCLUDE NAME: LOGGER_MQSYS_INCLUDE_PATH
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_BASE_INCLUDE_PATH
#include LOGGER_CODES_INCLUDE_PATH
#include LOGGER_CO_INCLUDE_PATH
#include LOGGER_WINDOW_LOGGER_INCLUDE_PATH



namespace logger {
	class LOGS_API log_q {
	public:
		log_q(logger::classic_log_window* lw_p);
		~log_q();

		void process_messages();

		void add_message(logger::log* log);

		std::atomic<bool> m_signal_b = false;
		std::condition_variable m_signal_cv;
	protected:
		void load_up();

		logger::classic_log_window* m_lw_p = nullptr;

		std::vector<log*>* m_vl_p = nullptr;

		std::queue<log*>* m_log_q = nullptr;

		std::mutex m_q_mtx;

		std::queue<log*>* m_log_q_buffer = nullptr;

		// process message boolean
		std::atomic<bool> m_run_pm = true;

		// mutex for m_vl_p
		std::mutex* m_v_mtx_p;
	};
}