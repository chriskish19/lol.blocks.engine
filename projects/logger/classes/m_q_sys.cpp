#include "m_q_sys.hpp"
/***************************************
*  File: m_q_sys.cpp (message queue system)
*
*  Purpose: m_q_sys.hpp definitions
*
*  Project: logger
* *************************************/

#include LOGGER_NAMES_INCLUDE
#include LOGGER_MQSYS_INCLUDE_PATH

logger::log_q::log_q()
{
	m_log_q = new std::queue<log*>;
	m_log_q_buffer = new std::queue<log*>;
}

logger::log_q::~log_q()
{
	while (m_log_q->empty() == false) {
		auto log = m_log_q->front();
		if (log != nullptr) {
			delete log;
		}
	}
	
	while (m_log_q_buffer->empty() == false) {
		auto log = m_log_q_buffer->front();
		if (log != nullptr) {
			delete log;
		}
	}
	

	if (m_log_q != nullptr) {
		delete m_log_q;
		m_log_q = nullptr;
	}

	if (m_log_q_buffer != nullptr) {
		delete m_log_q_buffer;
		m_log_q_buffer = nullptr;
	}
}

void logger::log_q::add_message(logger::log* log)
{
	std::unique_lock<std::mutex> local_lock(m_q_mtx);
	m_log_q_buffer->push(log);
}

void logger::log_q::exit()
{
	m_run_pm.store(false);
	m_signal_b.store(true);
	m_signal_cv.notify_all();
}


