/***************************************
*  File: m_q_sys.hpp (message queue system)
*
*  Purpose: buffer messages for the logger
*
*  Project: logger
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_BASE_INCLUDE_PATH
#include LOGGER_CODES_INCLUDE_PATH
#include LOGGER_CO_INCLUDE_PATH



namespace logger {
	class log_q {
	public:
		log_q(std::vector<log*>* vl_p);
		~log_q();

		void process_messages();

		void add_message(logger::log* log);

		void load_up();
	protected:

		std::vector<log*>* m_vl_p = nullptr;

		std::queue<log*>* m_log_q = nullptr;

		// signal to process message
		std::atomic<bool> m_signal_b = false;
		std::condition_variable m_signal_cv;

		std::mutex m_q_mtx;

		std::queue<log*>* m_log_q_buffer = nullptr;

		// process message boolean
		std::atomic<bool> m_run_pm = true;
	};
}