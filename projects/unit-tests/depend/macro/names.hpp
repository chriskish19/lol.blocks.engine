/***************************************
*  File: names.hpp
*
*  Purpose: easy file moves without breaking
*			include paths
* 
*  Project: tests
* *************************************/

// header libraries
#define TEST_STL_PRIVATE_INCLUDE_PATH				TEST_stl_includes_hpp					// the entire stl library
#define TEST_STL_INCLUDE_PATH						TEST_stl_hpp							// specific version include stl library

// macro
#define TEST_TYPES_INCLUDE_PATH						TEST_types_hpp							// types stuff

// classes
#define TEST_RANDOM_INCLUDE_PATH					TEST_random_hpp							// random generator

// api
#define TEST_API_INCLUDE_PATH						TEST_test_api_hpp						// test functions

// library include
#define TEST_ALL_TESTS_INCLUDE_PATH					TEST_all_tests_hpp						// include all test