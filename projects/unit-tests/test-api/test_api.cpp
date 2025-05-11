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
    logger::classic_log_window* terminal = new logger::classic_log_window;
    std::thread terminal_thread(&logger::classic_log_window::thread_go, terminal);
    terminal->wait_until_init();


    random data(32, 126);

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    while (std::chrono::steady_clock::now() < end_time) {
        string message = data.random_data_string(LOG_LENGTH - terminal->m_ts_length);
        terminal->send_message(message);
    }

    if (terminal_thread.joinable()) {
        terminal_thread.join();
    }

    if (terminal != nullptr) {
        delete terminal;
        terminal = nullptr;
    }
    return logger::codes::success;
}
