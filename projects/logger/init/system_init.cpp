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
	std::unique_ptr<system_log> glb_sl = std::make_unique<system_log>();
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
	log_terminal->send_message(message);
}

logger::codes logger::exit_system_log()
{
	log_terminal->send_message(ROS("waiting for log window to be closed..."));
	
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
		lt_thread = new std::thread(&logger::classic_log_window::thread_go, log_terminal);
	}
	catch (const logger::le& e) {
		// logger error
		CERROR << ROS("DESCRIPTION: ") << e.m_desc << '\n' <<
			ROS("WINOWS ERROR: ") << e.m_w32 << '\n' <<
			ROS("LOCATION: ") << e.m_loc;
	}
	catch (...) {
		CERROR << ROS("Unknown exception caught") << '\n' <<
			ROS("LOCATION: ") << gl();
	}
}

logger::system_log::~system_log()
{
	*this << ROS("log terminal window waiting to be closed...");
	
	if (lt_thread->joinable())
		lt_thread->join();

	if (lt_thread != nullptr) {
		delete lt_thread;
		lt_thread = nullptr;
	}

	if (log_terminal != nullptr) {
		delete log_terminal;
		log_terminal = nullptr;
	}
}

#endif
