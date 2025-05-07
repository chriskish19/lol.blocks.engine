/***************************************
*  File: wl.hpp (window logger)
*
*  Purpose: a window which displays 
*			system logs
*
*  Project: logger
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDS_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include BASE_INCLUDE_PATH
#include CO_INCLUDE_PATH


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
		virtual codes load();
	protected:
		// module handle
		HINSTANCE m_module = GetModuleHandle(NULL);

		// window handle
		HWND m_handle = nullptr;

		// class member function window procedure
		virtual LRESULT CALLBACK this_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// see above for definition
		// init in load()
		window_description m_wd;

		// window class
		// init in load()
		WNDCLASSEX m_wc;
	};



	// uses direct x to print the logs inside the window
	class LOGS_API dx_log_window : public logger::window {
	public:
		dx_log_window() = default;

		HWND handle() { return m_handle; }
		UINT width();
		UINT height();
	protected:
		LRESULT CALLBACK this_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	};


	// uses win32 api and classic window logging
	class LOGS_API classic_log_window : public logger::window {
	public:
		classic_log_window() = default;

	protected:
		LRESULT CALLBACK this_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	};
}