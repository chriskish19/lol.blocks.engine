#include "log_page.hpp"
/***************************************
*  File: log_page.cpp
*
*  Purpose: log_page.hpp definitions
*
*  Project: logger
* *************************************/

#include LOGGER_NAMES_INCLUDE
#include LOGGER_LP_INCLUDE_PATH

void logger::log_page::update(logger::log* log_p)
{
	if (log_p->m_index == 0)
		reset();
	
	log_p->m_lines += count_new_lines(*log_p->message);
	log_p->m_height *= log_p->m_lines;
	m_height += log_p->m_height;
	m_line_number = log_p->m_index;
}

void logger::log_page::reset()
{
	m_height = 0;
}
