/***************************************
*  File: log_api.hpp 
*
*  Purpose: helper functions
*
*  Project: logger
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDS_INCLUDE_PATH
#include CO_INCLUDE_PATH


namespace logger{
	// string conversions, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	// throws exception on error
	// {
	const size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const char* narrow);
	std::wstring to_wide_string(const std::string& narrow);
	std::string to_narrow_string(const wchar_t* wide);
	std::string to_narrow_string(const std::wstring& wide);
	// }


	// string conversions with error codes, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	// {
	std::wstring to_wide_string(const char* narrow, codes* code_p);
	std::wstring to_wide_string(const std::string& narrow, codes* code_p);
	std::string to_narrow_string(const wchar_t* wide, codes* code_p);
	std::string to_narrow_string(const std::wstring& wide, codes* code_p);
	// }


	// scrolling in a window
	// {

	// vertical movement
	// HWND : window handle
	// WPARAM : button push
	// vscroll_position : vertical scroll position
	// yChar : height of character
	codes vertical_drag(HWND hwnd, WPARAM wParam,int vscroll_position,int yChar);

	// horizontal movement
	// HWND : window handle
	// WPARAM : button push
	// hscroll_position : horizontal scroll position
	// xChar : width of character
	codes horizontal_drag(HWND hwnd, WPARAM wParam, int hscroll_position, int xChar);

	// window size changes for scrolling
	// HWND : window handle
	// WPARAM : button push
	// nol : total number of logger lines
	// yChar : height of a character
	// xChar : width of a character
	// xClientMax : maximum width of client area
	codes window_size_change(HWND hwnd, LPARAM lParam, int nol, int yChar, int xChar, int xClientMax);
	
	// }


	
	codes send_text(HWND window, const string& message);
}