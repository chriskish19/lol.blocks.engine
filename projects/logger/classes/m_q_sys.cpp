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

logger::log_q::log_q(logger::classic_log_window* lw_p)
	:m_lw_p(lw_p)
{
	if (m_lw_p == nullptr) {
		throw le(logger::codes::pointer_is_nullptr, pointer_is_nullptr_description);
	}
	
	m_log_q = new std::queue<log*>;
	m_log_q_buffer = new std::queue<log*>;

	auto inits = m_lw_p->get_qsys_inits();
	m_vl_p = inits.vp;
	m_v_mtx_p = inits.mtx_p;
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
	while (m_run_pm.load() == true) {

		// wait here
		std::mutex local_mtx;
		std::unique_lock<std::mutex> local_lock(local_mtx);
		m_signal_cv.wait(local_lock, [this]
			{
				return m_signal_b.load();
			});

		{
			std::unique_lock<std::mutex> local_lock(m_q_mtx);

			// swap with buffer
			m_log_q->swap(*m_log_q_buffer);
		}

		while (m_log_q->empty() == false) {
			// process queue
			logger::log* log_message = m_log_q->front();
			m_lw_p->send_log(log_message);
			m_log_q->pop();
		}

		m_signal_b.store(false);
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
