#include "base.hpp"
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
		m_logs_v->push_back(new log(i));
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

void logger::base::set_log(logger::log* log_p)
{
	*log_p->message = time_stamped(*log_p->message);

	// cycle
	if (m_v_index < (m_logs_v->size() - 1)) {
		// next log
		m_v_index++;
	}
	else {
		// reset
		m_v_index = 0;
	}
}

logger::string logger::base::time_stamped(const string& message)
{
	try {
		auto now = std::chrono::system_clock::now();
		string time = std::format(ROS("[{}]"), now);
		return time + message;
	}
	catch (const std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "unknown exception caught..." << std::endl;
	}
	// exception thrown we return nothing
	return {};
}
