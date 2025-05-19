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

	core::standard_window* window = new core::standard_window;
	{
		core::codes code = window->load();
		core::output_code(code);
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

	return static_cast<int>(msg.wParam);
}

#elif TEST_ENTRY

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	logger::glb_sl->get_terminal_p()->wait_until_init();

	logger::codes code = test::classic_log_terminal(10,1);
	return static_cast<int>(code);
}


// gives a terminal console
/*
int main() {
	// Prepare arguments for wWinMain
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	HINSTANCE hPrevInstance = nullptr;
	LPWSTR lpCmdLine = GetCommandLineW();
	int nShowCmd = SW_SHOW;

	// Call wWinMain
	return wWinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}
*/


#endif