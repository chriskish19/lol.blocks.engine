/***************************************
*  File: scroll.hpp (scrolling)
*
*  Purpose: handle scrolling in a window
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDS_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include CO_INCLUDE_PATH



namespace logger {
	// classic win32 window scrolling
	class classic_scroll {
	public:
		classic_scroll() = default;

		codes vertical_drag(HWND hwnd, WPARAM wParam);
		codes horizontal_drag(HWND hwnd, WPARAM wParam);

		codes window_size_change(HWND hwnd, LPARAM lParam);

		void set_v_position(int v_pos) { m_vscroll_position = v_pos; }
		void set_h_position(int h_pos) { m_hscroll_position = h_pos; }

		int get_v_position() { return m_vscroll_position; }
		int get_h_position() { return m_hscroll_position; }

		int get_vertical_unit() { return m_yChar; }
		int get_horizontal_unit() { return m_xChar; }
	protected:
		int m_vscroll_position = 0;						// current vertical scrolling position 
		int m_hscroll_position = 0;						// current horizontal scrolling position 

		int m_xChar = 0;								// horizontal scrolling unit 
		int m_yChar = 0;								// vertical scrolling unit 
		int m_xUpper = 0;								// average width of uppercase letters

		int m_yClient = 0;								// height of client area
		int m_xClient = 0;								// width of client area

		int m_xClientMax = 0;							// maximum width of client area

		int m_FirstLine = 0;							// first line in the invalidated area 
		int m_LastLine = 0;								// last line in the invalidated area 
	};


	// direct x window scrolling
	class dx_scroll {
	public:



	protected:

	};
}