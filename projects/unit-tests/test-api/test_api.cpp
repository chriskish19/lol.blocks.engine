#include "test_api.hpp"
/***************************************
*  File: test_api.cpp
*
*  Purpose: test_api.hpp definitions
*
*  Project: tests
* *************************************/


#include TEST_NAMES_INCLUDE
#include TEST_API_INCLUDE_PATH

logger::codes TEST_API test::classic_log_terminal(std::size_t seconds)
{
#if MANUAL_LOGGER 

    logger::init_system_log();

    random data(32, 126);

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    while (std::chrono::steady_clock::now() < end_time) {
        string message = data.random_data_string(LOG_LENGTH - logger::log_terminal->m_ts_length);
        logger::log_message(message);
    }

    return logger::exit_system_log();

#else

    random data(32, 126);
    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    while (std::chrono::steady_clock::now() < end_time) {
        string message = data.random_data_string(LOG_LENGTH - logger::glb_sl->m_ts_length);
        logger::glb_sl->log_message(message);
    }
    return logger::codes::success;
#endif
}

logger::codes TEST_API test::classic_log_terminal(std::size_t seconds, std::size_t pause)
{
#if MANUAL_LOGGER

    logger::init_system_log();

    random data(32, 126);

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    while (std::chrono::steady_clock::now() < end_time) {
        string message = data.random_data_string(LOG_LENGTH - logger::log_terminal->m_ts_length);
        logger::log_message(message);
        std::this_thread::sleep_for(std::chrono::seconds(pause));
    }

    return logger::exit_system_log();

#else
    std::mutex local_mtx;
    random data(32, 126);
    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    while (std::chrono::steady_clock::now() < end_time) {
        string message = data.random_data_string(LOG_LENGTH - logger::glb_sl->m_ts_length);
        
        {
            std::unique_lock<std::mutex> local_lock;
            logger::glb_sl->log_message(message);
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(pause));
    }
    return logger::codes::success;
#endif
}
