/***************************************
*  File: main.cpp
*
*  Purpose: main entry into the program
*
*  Project: core
* *************************************/



#include CORE_NAMES_INCLUDE
#include CORE_ALL_CORE_INCLUDE_PATH

#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_ENGINE_INCLUDE_PATH

#include GUI_NAMES_INCLUDE
#include GUI_ALL_GUI_INCLUDE_PATH

#include LOGGER_NAMES_INCLUDE
#include LOGGER_ALL_LOGS_INCLUDE_PATH

#include TEST_NAMES_INCLUDE
#include TEST_ALL_TESTS_INCLUDE_PATH


#if MAIN_ENTRY

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	logger::classic_log_window* log_terminal = new logger::classic_log_window;
	std::jthread lt_thread(&logger::classic_log_window::thread_go, log_terminal);


	core::standard_window* window = new core::standard_window;
	{
		core::codes code = window->load();
		if (code != core::codes::success) {
			if (window != nullptr) {
				delete window;
				window = nullptr;
			}
			return static_cast<int>(code);
		}
	}


	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// render here
		}
	}

	if (window != nullptr) {
		delete window;
		window = nullptr;
	}

	if (log_terminal != nullptr) {
		delete log_terminal;
		log_terminal = nullptr;
	}

	return static_cast<int>(msg.wParam);
}

#elif TEST_ENTRY

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	test::classic_log_terminal(30);
	return 0;
}


#endif