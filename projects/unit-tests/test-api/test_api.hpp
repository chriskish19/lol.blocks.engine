/***************************************
*  File: test_api.hpp
*
*  Purpose: testing of all projects
*
*  Project: tests
* *************************************/

#pragma once

// tests library dependencies
#include TEST_NAMES_INCLUDE
#include TEST_STL_INCLUDE_PATH
#include TEST_TYPES_INCLUDE_PATH
#include TEST_RANDOM_INCLUDE_PATH

// entire engine library
#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_ENGINE_INCLUDE_PATH

// entire gui library
#include GUI_NAMES_INCLUDE
#include GUI_ALL_GUI_INCLUDE_PATH

// entire logger library
#include LOGGER_NAMES_INCLUDE
#include LOGGER_ALL_LOGS_INCLUDE_PATH


namespace test {
	// fast test
	logger::codes TEST_API classic_log_terminal(std::size_t seconds);

	// slow test
	logger::codes TEST_API classic_log_terminal(std::size_t seconds, std::size_t pause);
}