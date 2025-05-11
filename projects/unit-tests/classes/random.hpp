/***********************************************
* File: random.hpp
*
* Purpose: generate random data, for testing
*
* Project: unit-tests
*
************************************************/

#pragma once
#include TEST_NAMES_INCLUDE
#include TEST_STL_INCLUDE_PATH
#include TEST_TYPES_INCLUDE_PATH



namespace test {
	class random {
	public:
		random(std::size_t rlow, std::size_t rhigh);

		string random_data_string(std::size_t length);
	protected:
		std::random_device m_rd;
		std::mt19937 m_gen;
		std::uniform_int_distribution<int> m_dist;
	};
}