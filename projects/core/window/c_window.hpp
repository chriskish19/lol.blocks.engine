/***************************************
*  File: c_window.hpp (core window)
*
*  Purpose: house window classes
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include TYPES_INCLUDE_PATH

#include CODES_INCLUDE_PATH
#include WIN_INCLUDE_PATH
#include STL_INCLUDE_PATH

namespace core {
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




	class standard_window {
	public:
		// window is default init
		standard_window() = default;

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
			ROS("StandardWindow"),
			ROS("lol.blocks.engine"),
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
		   LoadIcon(nullptr, IDI_APPLICATION),
		   LoadCursor(nullptr, IDC_ARROW),
		   reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
		   nullptr,
		   ROS("StandardWindow"),
		   LoadIcon(nullptr, IDI_APPLICATION)
		};

	};
}