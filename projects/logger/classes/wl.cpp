#include "wl.hpp"
/***************************************
*  File: wl.cpp (window logger)
*
*  Purpose: wl.hpp definitions
*
*  Project: logger
* *************************************/

#include LOGGER_NAMES_INCLUDE
#include LOGGER_WINDOW_LOGGER_INCLUDE_PATH

HWND logger::create_window(const window_description& wd) {
    /*

    HWND CreateWindowExW(
          [in]           DWORD     dwExStyle,
          [in, optional] LPCWSTR   lpClassName,
          [in, optional] LPCWSTR   lpWindowName,
          [in]           DWORD     dwStyle,
          [in]           int       X,
          [in]           int       Y,
          [in]           int       nWidth,
          [in]           int       nHeight,
          [in, optional] HWND      hWndParent,
          [in, optional] HMENU     hMenu,
          [in, optional] HINSTANCE hInstance,
          [in, optional] LPVOID    lpParam
        );

    */

    return CreateWindowEx(
        wd.dwExStyle,
        wd.lpClassName,
        wd.lpWindowName,
        wd.dwStyle,
        wd.X,
        wd.Y,
        wd.nWidth,
        wd.nHeight,
        wd.hWndParent,
        wd.hMenu,
        wd.hInstance,
        wd.lpParam
    );
}

logger::codes logger::register_window(const WNDCLASSEX& wc) {
    ATOM atm = RegisterClassEx(&wc);

    if (atm == 0) {
        return codes::register_class_fail;
    }

    return codes::success;
}

LRESULT logger::window::s_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // reroute to private window proc
    window* p_window_rerouter = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        // Store the pointer to the window instance in the user data associated with the HWND.
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_window_rerouter = (window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)p_window_rerouter);
    }
    else
    {
        // Retrieve the pointer to the window instance from the user data associated with the HWND.
        p_window_rerouter = (window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (p_window_rerouter)
    {
        return p_window_rerouter->this_window_proc(hwnd, uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

logger::codes logger::window::load()
{
    if (m_module == nullptr) {
        return codes::module_handle_error;
    }
    
    
    m_wd = window_description{
            NULL,
            ROS("LogWindow"),
            ROS("System Log"),
            WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            m_module,
            this
    };

    /*
    
    typedef struct tagWNDCLASSEXW {
              UINT      cbSize;
              UINT      style;
              WNDPROC   lpfnWndProc;
              int       cbClsExtra;
              int       cbWndExtra;
              HINSTANCE hInstance;
              HICON     hIcon;
              HCURSOR   hCursor;
              HBRUSH    hbrBackground;
              LPCWSTR   lpszMenuName;
              LPCWSTR   lpszClassName;
              HICON     hIconSm;
            } WNDCLASSEXW, *PWNDCLASSEXW, *NPWNDCLASSEXW, *LPWNDCLASSEXW;

    */

    m_wc = WNDCLASSEX{
       sizeof(WNDCLASSEX),
       0,
       s_window_proc,
       0,
       0,
       m_module,
       ExtractIcon(m_module, ROS("shell32.dll"), 15),
       LoadCursor(nullptr, IDC_ARROW),
       reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
       nullptr,
       ROS("LogWindow"),
       ExtractIcon(m_module, ROS("shell32.dll"), 15)
    };
    
    
    {
        codes code = register_window(m_wc);
        if (code != codes::success) {
            return code;
        }
    }

    m_handle = create_window(m_wd);

    if (m_handle == nullptr) {
        return codes::hwnd_error;
    }
    else {
        ShowWindow(m_handle, SW_SHOW);
    }

    return codes::success;
}

LRESULT logger::window::this_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    } // end of switch (uMsg)

    // no default switches needed
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

UINT logger::dx_log_window::width()
{
    RECT rc = {};
    if (GetClientRect(m_handle, &rc) == FALSE) {
        throw le(codes::get_client_rect_fail, get_client_rect_fail_description);
    }
    return rc.bottom - rc.top;
}

UINT logger::dx_log_window::height()
{
    RECT rc = {};
    if (GetClientRect(m_handle, &rc) == FALSE) {
        throw le(codes::get_client_rect_fail, get_client_rect_fail_description);
    }
    return rc.right - rc.left;
}

LRESULT logger::dx_log_window::this_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {

    }

    return logger::window::this_window_proc(hwnd, uMsg, wParam, lParam);
}

logger::classic_log_window::classic_log_window()
    :base(LOGGER_LINES)
{
    
}

logger::classic_log_window::~classic_log_window()
{
    
}

logger::codes logger::classic_log_window::load()
{
    {
        // call the base function for regular setup
        codes code = logger::window::load();
        if (code != codes::success) {
            return code;
        }
    }

    // Create and select a custom font
    m_clw_font = CreateFont(
        m_font_size,                 // Height
        0,                         // Width (0 for default)
        0,                         // Escapement
        0,                         // Orientation
        FW_BOLD,                   // Weight (FW_NORMAL, FW_BOLD, etc.)
        FALSE,                     // Italic
        FALSE,                     // Underline
        FALSE,                     // Strikeout
        DEFAULT_CHARSET,           // Character set
        OUT_DEFAULT_PRECIS,        // Output precision
        CLIP_DEFAULT_PRECIS,       // Clipping precision
        ANTIALIASED_QUALITY,       // Quality
        DEFAULT_PITCH | FF_SWISS,  // Pitch and family
        ROS("Arial")               // Font face name
    );

    if (m_clw_font == nullptr) {
        return codes::font_nullptr;
    }

    RECT wl_rect;
    if (GetClientRect(m_handle, &wl_rect) == FALSE) {
        return codes::get_client_rect_fail;
    }

    return codes::success;
}

void logger::classic_log_window::thread_go()
{
    {
        codes code = load();
        if (code != codes::success) {
            er_co_out(code);
            return;
        }
    }

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, m_handle, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

logger::codes logger::classic_log_window::wait_until_init()
{
    // wait here
    std::mutex local_mtx;
    std::unique_lock<std::mutex> local_lock(local_mtx);
    m_wait_cv.wait(local_lock, [this]
        {
            return m_wait_b.load();
        });

    return codes::success;
}

LRESULT logger::classic_log_window::this_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    

    try {
        SCROLLINFO si;
        HDC hdc;
        PAINTSTRUCT ps;
        TEXTMETRIC tm;

        int FirstLine;          // first line in the invalidated area 
        int LastLine;           // last line in the invalidated area 

        int i;                  // loop counter 
        int x, y;               // horizontal and vertical coordinates

        switch (uMsg) {

            case WM_CREATE:
            {
                // GET TEXT SIZES when the window is first created.

                // Get the handle to the client area's device context. 
                hdc = GetDC(m_handle);

                // use custom font object
                SelectObject(hdc, m_clw_font);

                // Extract font dimensions from the text metrics. 
                if (GetTextMetrics(hdc, &tm) == FALSE) {
                    throw le(codes::get_text_metrics_fail,get_text_metrics_fail_description);
                }

                // calculate sizes
                m_xChar = tm.tmAveCharWidth;
                m_xUpper = (tm.tmPitchAndFamily & 1 ? 3 : 2) * m_xChar / 2;
                m_yChar = tm.tmHeight + 2;

                // Free the device context. 
                ReleaseDC(m_handle, hdc);

                // max log size
                m_xClientMax = LOG_LENGTH * m_xChar;
              
                return 0;
            }

            case WM_SHOWWINDOW:
            {
                // prevent thread from adavancing before window is displayed
                // window logger window was successfully created
                if (hwnd == m_handle) {

                    // tell waiting thread its safe to procceed...
                    m_wait_b.store(true);
                    m_wait_cv.notify_all();
                }
                
                return 0;
            }

            case WM_SIZE:
            {
                // Retrieve the dimensions of the client area. 
                m_yClient = HIWORD(lParam);
                m_xClient = LOWORD(lParam);

                // Set the vertical scrolling range and page size
                si.cbSize = sizeof(si);
                si.fMask = SIF_RANGE | SIF_PAGE;
                si.nMin = 0;
                si.nMax = LOGGER_LINES - 1;
                si.nPage = m_yClient / m_yChar;
                SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

                // Set the horizontal scrolling range and page size. 
                si.cbSize = sizeof(si);
                si.fMask = SIF_RANGE | SIF_PAGE;
                si.nMin = 0;
                si.nMax = 2 + m_xClientMax / m_xChar;
                si.nPage = m_xClient / m_xChar;
                SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
                
                return 0;
            }

            case WM_HSCROLL:
            {
                // Get all the vertial scroll bar information.
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;

                // Save the position for comparison later on.
                GetScrollInfo(hwnd, SB_HORZ, &si);
                m_xPos = si.nPos;
                switch (LOWORD(wParam))
                {
                    // User clicked the left arrow.
                case SB_LINELEFT:
                    si.nPos -= 1;
                    break;

                    // User clicked the right arrow.
                case SB_LINERIGHT:
                    si.nPos += 1;
                    break;

                    // User clicked the scroll bar shaft left of the scroll box.
                case SB_PAGELEFT:
                    si.nPos -= si.nPage;
                    break;

                    // User clicked the scroll bar shaft right of the scroll box.
                case SB_PAGERIGHT:
                    si.nPos += si.nPage;
                    break;

                    // User dragged the scroll box.
                case SB_THUMBTRACK:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
                }

                // Set the position and then retrieve it.  Due to adjustments
                // by Windows it may not be the same as the value set.
                si.fMask = SIF_POS;
                SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
                GetScrollInfo(hwnd, SB_HORZ, &si);

                // If the position has changed, scroll the window.
                if (si.nPos != m_xPos)
                {
                    ScrollWindow(hwnd, m_xChar * (m_xPos - si.nPos), 0, NULL, NULL);
                }

                return 0;
            }

            case WM_VSCROLL:
            {
                // Get all the vertial scroll bar information.
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwnd, SB_VERT, &si);

                // Save the position for comparison later on.
                m_yPos = si.nPos;
                switch (LOWORD(wParam))
                {

                    // User clicked the HOME keyboard key.
                case SB_TOP:
                    si.nPos = si.nMin;
                    break;

                    // User clicked the END keyboard key.
                case SB_BOTTOM:
                    si.nPos = si.nMax;
                    break;

                    // User clicked the top arrow.
                case SB_LINEUP:
                    si.nPos -= 1;
                    break;

                    // User clicked the bottom arrow.
                case SB_LINEDOWN:
                    si.nPos += 1;
                    break;

                    // User clicked the scroll bar shaft above the scroll box.
                case SB_PAGEUP:
                    si.nPos -= si.nPage;
                    break;

                    // User clicked the scroll bar shaft below the scroll box.
                case SB_PAGEDOWN:
                    si.nPos += si.nPage;
                    break;

                    // User dragged the scroll box.
                case SB_THUMBTRACK:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
                }

                // Set the position and then retrieve it.  Due to adjustments
                // by Windows it may not be the same as the value set.
                si.fMask = SIF_POS;
                SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
                GetScrollInfo(hwnd, SB_VERT, &si);

                // If the position has changed, scroll window and update it.
                if (si.nPos != m_yPos)
                {
                    ScrollWindow(hwnd, 0, m_yChar * (m_yPos - si.nPos), NULL, NULL);
                    UpdateWindow(hwnd);
                }

                return 0;
            }

            case WM_PAINT:
            {   
                // Prepare the window for painting.
                hdc = BeginPaint(hwnd, &ps);

                // Get vertical scroll bar position.
                si.cbSize = sizeof(si);
                si.fMask = SIF_POS;
                GetScrollInfo(hwnd, SB_VERT, &si);
                m_yPos = si.nPos;

                // Get horizontal scroll bar position.
                GetScrollInfo(hwnd, SB_HORZ, &si);
                m_xPos = si.nPos;

                // Find painting limits.
                FirstLine = std::max(0, m_yPos + (int)ps.rcPaint.top / m_yChar);
                LastLine = std::min(LOGGER_LINES - 1, m_yPos + (int)ps.rcPaint.bottom / m_yChar);

                for (i = FirstLine; i <= LastLine; i++)
                {
                    x = m_xChar * (1 - m_xPos);
                    y = m_yChar * (i - m_yPos);

                    auto log = base::get_buffer()->at(i);

                    // Write a line of text to the client area.
                    TextOut(hdc, x, y, log->message->c_str(), log->message->size());
                }

                // Indicate that painting is finished.
                EndPaint(hwnd, &ps);
                return 0;
            }
        } // end of switch
    }
    catch (const logger::le& e) {
        string output = ROS("DESCRIPTION: ") + e.m_desc + ROS('\n') + ROS("WINDOWS ERROR: ") + e.m_w32
            + ROS('\n') + ROS("LOCATION: ") + e.m_loc + ROS('\n');
        OutputDebugString(output.c_str());
    }
    catch (...) {
        logger::le e(logger::codes::unknown_exception_caught, unknown_exception_caught_description);
        string output = ROS("DESCRIPTION: ") + e.m_desc + ROS('\n') + ROS("WINDOWS ERROR: ") + e.m_w32
            + ROS('\n') + ROS("LOCATION: ") + e.m_loc + ROS('\n');
        OutputDebugString(output.c_str());
    }


    return logger::window::this_window_proc(hwnd, uMsg, wParam, lParam);
}