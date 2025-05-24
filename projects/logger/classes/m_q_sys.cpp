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

logger::log_q::log_q(std::vector<log*>* vl_p)
	:m_vl_p(vl_p)
{
	if (m_vl_p == nullptr) {
		throw le(logger::codes::pointer_is_nullptr, pointer_is_nullptr_description);
	}
	
	m_log_q = new std::queue<log*>;
	m_log_q_buffer = new std::queue<log*>;

	for (auto log : *vl_p) {
		if (log->message->empty()) {
			break;
		}
		else {
			m_log_q->push(log);
		}
	}


}

logger::log_q::~log_q()
{
	if (m_log_q != nullptr) {
		delete m_log_q;
		m_log_q = nullptr;
	}

	if (m_log_q_buffer != nullptr) {
		delete m_log_q_buffer;
		m_log_q_buffer = nullptr;
	}
}

void logger::log_q::process_messages()
{
	


	while (m_run_pm.load()) {

		// wait here
		std::mutex local_mtx;
		std::unique_lock<std::mutex> local_lock(local_mtx);
		m_signal_cv.wait(local_lock, [this]
			{
				return m_signal_b.load();
			});

		// load up buffer
		load_up(); 

		{
			std::unique_lock<std::mutex> local_lock(m_q_mtx);
			
			// swap with buffer
			m_log_q->swap(*m_log_q_buffer);
		}

		// process queue

	}
}

void logger::log_q::add_message(logger::log* log)
{
	std::unique_lock<std::mutex> local_lock(m_q_mtx);
	m_log_q_buffer->push(log);
}

void logger::log_q::load_up()
{
	for (auto log : *m_vl_p) {
		if (log->message->empty()) {
			break;
		}
		else {
			m_log_q_buffer->push(log);
		}
	}
}
