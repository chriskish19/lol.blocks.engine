/***************************************
*  File: log_api.hpp 
*
*  Purpose: helper functions
*
*  Project: logger
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_CO_INCLUDE_PATH


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

	// vertical movement on the scroll bar
	// HWND hwnd : window handle
	// WPARAM wParam : button push
	// int vscroll_position : vertical scroll position
	// int yChar : height of character
	codes vertical_drag(HWND hwnd, WPARAM wParam,int vscroll_position,int yChar);

	// horizontal movement on the scroll bar
	// HWND hwnd: window handle
	// WPARAM wParam: button push
	// int hscroll_position : horizontal scroll position
	// int xChar : width of character
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


	// send text to a window
	// HWND window : window handle
	// const string& message : text message to display
	// RECT position : the position in the window to display the text
	codes send_text(HWND window,const string* message,RECT position);

	// send text to a window
	// HDC hdc : handle to device context
	// const string& message : text message to display
	// RECT position : the position in the window to display the text
	codes send_text(HDC hdc,const string* message, RECT position);


	// simple time stamp a message
	// returns the message with a time on it ([2025-05-09-14:00:30...])
	string time_stamped(const string& message);

	// log a CO object to the output window
	void er_co_out(codes code);
}