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
		logger::classic_log_window::load();
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

}

void logger::system_log::log_message(const string& message)
{
	// get current log
	logger::log* log_p = nullptr;
	std::size_t index = 0;
	
	index = base::get_v_index();
	log_p = base::get_buffer()->at(index);
	*log_p->message = message;
	
	base::set_log(log_p);

	InvalidateRect(m_handle, nullptr, false);
	UpdateWindow(m_handle);
}

#endif
