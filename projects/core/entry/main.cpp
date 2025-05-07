/***************************************
*  File: main.cpp
*
*  Purpose: main entry into the program
*
*  Project: core
* *************************************/


#include NAMES_INCLUDE
#include ALL_CORE_INCLUDE_PATH

// dll project headers
#include "all_engine.hpp"
#include "all_gui.hpp"


int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
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

	return static_cast<int>(msg.wParam);
}