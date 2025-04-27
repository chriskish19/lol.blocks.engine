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
	core::standard_window* test_window = new core::standard_window;

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

	return static_cast<int>(msg.wParam);
}