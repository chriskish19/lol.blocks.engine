/***************************************
*  File: wl.hpp (window logger)
*
*  Purpose: a window which displays 
*			system logs
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDS_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include BASE_INCLUDE_PATH


namespace logger {
	struct window_description {
		DWORD					dwExStyle;    // The extended window style of the window being created
		const_character_p		lpClassName;  // The class name of the window
		const_character_p		lpWindowName; // The name/title of the window
		DWORD					dwStyle;      // The style of the window
		int						X;            // The initial horizontal position of the window
		int						Y;            // The initial vertical position of the window
		int						nWidth;       // The width of the window
		int						nHeight;      // The height of the window
		HWND					hWndParent;   // Handle to the parent or owner window
		HMENU					hMenu;        // Handle to a menu, or child-window identifier
		HINSTANCE				hInstance;    // Handle to the instance of the module to be associated with the window
		LPVOID					lpParam;      // Pointer to additional application-defined data
	};

	// create a window from a window description
	HWND create_window(const window_description& wd);

	// register a window class
	codes register_window(const WNDCLASSEX& wc);
	
	
	
	class LOGS_API window {
	public:
		window() = default;

		// static window procedure
		static LRESULT CALLBACK s_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// initialize the window
		codes load();
	protected:
		// window handle
		HWND m_handle = nullptr;

		// class member function window procedure
		LRESULT CALLBACK this_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


		window_description m_wd = {
			NULL,
			ROS("LogWindow"),
			ROS("System Log"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			this
		};


		WNDCLASSEX m_wc = {
		   sizeof(WNDCLASSEX),
		   CS_HREDRAW | CS_VREDRAW,
		   s_window_proc,
		   0,
		   0,
		   GetModuleHandle(NULL),
		   ExtractIcon(GetModuleHandle(NULL), ROS("shell32.dll"), 15),
		   LoadCursor(nullptr, IDC_ARROW),
		   reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
		   nullptr,
		   ROS("LogWindow"),
		   ExtractIcon(GetModuleHandle(NULL), ROS("shell32.dll"), 15)
		};
	};
}