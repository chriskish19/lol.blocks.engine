#include "system_init.hpp"
/***************************************
*  File: system_init.cpp (system initialize)
*
*  Purpose: system_init.hpp definitions
*
*  Project: logger
* *************************************/

#include LOGGER_NAMES_INCLUDE
#include LOGGER_SYSINIT_INCLUDE_PATH


namespace logger {
#if MANUAL_LOGGER
	logger::classic_log_window* log_terminal = nullptr;
	std::thread* lt_thread = nullptr;
#else
	// automatic system logger
	std::unique_ptr<system_log> glb_sl = nullptr;
#endif
}


#if MANUAL_LOGGER
logger::codes logger::init_system_log()
{
	try {
		log_terminal = new logger::classic_log_window;
		lt_thread = new std::thread(&logger::classic_log_window::thread_go, log_terminal);
		log_terminal->wait_until_init();
	}
	catch (const logger::le& e) {
		// logger error
		CERROR << ROS("DESCRIPTION: ") << e.m_desc << '\n' <<
			ROS("WINOWS ERROR: ") << e.m_w32 << '\n' <<
			ROS("LOCATION: ") << e.m_loc;
		return codes::logger_exception_caught;
	}
	catch (...) {
		CERROR << ROS("Unknown exception caught") << '\n' <<
			ROS("LOCATION: ") << gl();
		return codes::unknown_exception_caught;
	}
	return codes::success;
}

void logger::log_message(const string& message)
{
	log_terminal->send_log(message);
}

logger::codes logger::exit_system_log()
{
	log_terminal->send_log(ROS("waiting for log window to be closed..."));
	
	if(lt_thread->joinable())
		lt_thread->join();


	if (lt_thread != nullptr) {
		delete lt_thread;
		lt_thread = nullptr;
	}

	if (log_terminal != nullptr) {
		delete log_terminal;
		log_terminal = nullptr;
	}

	return codes::success;
}

#else

logger::system_log::system_log()
{
	try {
		log_terminal = new logger::classic_log_window;
		log_terminal->load();

		m_lq = new logger::log_q(log_terminal);
		m_qsys_thread = new std::thread(&logger::log_q::process_messages, m_lq);

		alloc_new_logs();
	}
	catch (const logger::le& e) {
		string output = ROS("DESCRIPTION: ") + e.m_desc + ROS('\n') + ROS("WINDOWS ERROR: ") + e.m_w32
			+ ROS('\n') + ROS("LOCATION: ") + e.m_loc + ROS('\n');
		OutputDebugString(output.c_str());
	}
	catch (...) {
		logger::le e(logger::codes::unknown_exception_caught, unknown_exception_caught_description);
		string output = ROS("DESCRIPTION: ") + e.m_desc + ROS('\n') + ROS("WINDOWS ERROR: ") + e.m_w32
			+ ROS('\n') + ROS("LOCATION: ") + e.m_loc + ROS('\n');
		OutputDebugString(output.c_str());
	}
}

logger::system_log::~system_log()
{	
	dealloc_logs();

	if (m_qsys_thread->joinable())
		m_qsys_thread->join();

	if (m_qsys_thread != nullptr) {
		delete m_qsys_thread;
		m_qsys_thread = nullptr;
	}

	if (m_lq != nullptr) {
		delete m_lq;
		m_lq = nullptr;
	}

	if (log_terminal != nullptr) {
		delete log_terminal;
		log_terminal = nullptr;
	}
}

void logger::system_log::system_log_flush()
{
	m_lq->m_signal_b.store(true);
	m_lq->m_signal_cv.notify_all();
}

void logger::system_log::alloc_new_logs()
{
	for (std::size_t i = 0; i < LOGGER_LINES; ++i) {
		logger::log* log_p = new log(i);
		m_logp_v.push_back(log_p);
	}
}

void logger::system_log::dealloc_logs()
{
	for (auto log : m_logp_v) {
		if (log != nullptr) {
			delete log;
			log = nullptr;
		}
	}

	m_logp_v.erase(m_logp_v.begin(), m_logp_v.end());
}

std::size_t logger::system_log::at_index()
{
	if (m_index < m_logp_v.size() - 1) {
		m_index++;
	}
	else {
		m_index = 0;
		return m_index;
	}

	return std::size_t(m_index-1);
}

#endif
