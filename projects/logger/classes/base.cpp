/***************************************
*  File: base.cpp
*
*  Purpose: base.hpp definitions
*
*  Project: logger
* *************************************/

#include LOGGER_NAMES_INCLUDE
#include LOGGER_BASE_INCLUDE_PATH

logger::base::base(std::size_t nol) {
	// allocate the logs vector and fill
	m_logs_v = new std::vector<log*>;
	m_logs_v->reserve(nol);
	for (std::size_t i = 0; i < nol; ++i) {
		m_logs_v->push_back(new log());
	}
}

logger::base::~base()
{
	for (auto log : *m_logs_v) {
		if (log != nullptr) {
			delete log;
		}
	}
	
	if (m_logs_v != nullptr) {
		delete m_logs_v;
		m_logs_v = nullptr;
	}
}

void logger::base::set_message(const string& message)
{
	// get current log message
	auto current_log = m_logs_v->at(m_index);

	// copy
	*current_log->message = time_stamped(message);

	// cycle
	if (m_index < (m_logs_v->size() - 1)) {
		m_index++;
	}
	else {
		// reset
		m_index = 0;
	}
}
