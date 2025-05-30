/***************************************
*  File: log_page.hpp
*
*  Purpose: hold values useful for a log window
*
*  Project: logger
* 
*  Include name: LOGGER_LP_INCLUDE_PATH
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_BASE_INCLUDE_PATH
#include LOGGER_LOG_API_INCLUDE_PATH


namespace logger {
	class log_page {
	public:
		log_page() = default;

		void update(logger::log* log_p);
		void reset();
	protected:
		const std::size_t m_max_logs = LOGGER_LINES;
		const std::size_t m_font_size = LOGGER_FONT_SIZE;
		std::size_t m_line_number = 0;
		std::size_t m_height = 0;
	};
}