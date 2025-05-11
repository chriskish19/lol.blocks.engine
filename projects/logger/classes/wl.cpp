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


    m_wc = WNDCLASSEX{
       sizeof(WNDCLASSEX),
       CS_HREDRAW | CS_VREDRAW,
       s_window_proc,
       0,
       0,
       GetModuleHandle(NULL),
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

    HDC hdc;
    TEXTMETRIC tm;

    // Get the handle to the client area's device context. 
    hdc = GetDC(m_handle);

    // use custom font object
    SelectObject(hdc, m_clw_font);

    // Extract font dimensions from the text metrics. 
    if (GetTextMetrics(hdc, &tm) == FALSE) {
        return codes::get_text_metrics_fail;
    }

    m_xChar = tm.tmAveCharWidth;
    m_xUpper = (tm.tmPitchAndFamily & 1 ? 3 : 2) * m_xChar / 2;
    m_yChar = tm.tmHeight + tm.tmExternalLeading;

    // Free the device context. 
    ReleaseDC(m_handle, hdc);

    m_xClientMax = LOG_LENGTH * m_xChar;

    return codes::success;
}

void logger::classic_log_window::send_message(const string& message)
{
    std::lock_guard<std::mutex> local_lock(m_message_mtx);
    
    log_foundation.set_message(message);

    auto log_buffer_p = log_foundation.get_buffer();
    auto log = log_buffer_p->at(log_foundation.get_index());

    // update window
    InvalidateRect(m_handle, log->window_position , TRUE);
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
    while (GetMessage(&msg, NULL, 0, 0) > 0)
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

std::size_t logger::classic_log_window::get_time_length()
{
    string time = time_stamped(ROS(""));
    return time.size();
}

LRESULT logger::classic_log_window::this_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_SHOWWINDOW:
        {
            // window logger window was successfully created
            if (hwnd == m_handle) {

                // tell waiting thread its safe to procceed...
                m_wait_b.store(true);
                m_wait_cv.notify_all();
            }
            break;
        }
    
        case WM_SIZE:
        {
            window_size_change(m_handle, lParam, m_nol, m_yChar, m_xChar, m_xClientMax);
            break;
        }

        case WM_HSCROLL:
        {
            horizontal_drag(m_handle, wParam, m_hscroll_position, m_xChar);
            break;
        }

        case WM_VSCROLL: 
        {
            vertical_drag(m_handle, wParam, m_vscroll_position, m_yChar);
            break;
        }

        case WM_PAINT:
        {
            std::lock_guard<std::mutex> local_lock(m_message_mtx);
            
            RECT wl_rect = {};
            if (GetClientRect(hwnd, &wl_rect) == FALSE) {
                er_co_out(codes::get_client_rect_fail);
            }

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // get a si object
            SCROLLINFO si = {};

            // Get vertical scroll bar position.
            si.cbSize = sizeof(si);
            si.fMask = SIF_POS;
            GetScrollInfo(hwnd, SB_VERT, &si);
            m_vscroll_position = si.nPos;

            // Get horizontal scroll bar position.
            GetScrollInfo(hwnd, SB_HORZ, &si);
            m_hscroll_position = si.nPos;

            FillRect(hdc, &wl_rect, (HBRUSH)(COLOR_WINDOW + 1));

            // number of lines to print
            std::size_t nol_to_p = static_cast<std::size_t>((wl_rect.bottom - wl_rect.top) / m_yChar);

            std::size_t first_line = m_vscroll_position;
            std::size_t last_line = first_line + nol_to_p;

            auto log_buffer = log_foundation.get_buffer();

            std::size_t counter = 0;
            for (std::size_t i = first_line; i < last_line and i < log_buffer->size(); ++i) {
                // get log
                auto log = log_buffer->at(i);

                // calculate tops
                std::size_t top = wl_rect.top + (counter * m_yChar);
                counter++;

                // calculate bottoms
                std::size_t bottom = top + m_yChar;

                // set rects
                *log->window_position = RECT(wl_rect.left, top, wl_rect.right, bottom);

                // write to terminal window
                codes code = send_text(hdc, log->message, *log->window_position);
                if (code != codes::success) {
                    er_co_out(code);
                }
            }

            EndPaint(hwnd, &ps);
            break;
        }
    }

    return logger::window::this_window_proc(hwnd, uMsg, wParam, lParam);
}
