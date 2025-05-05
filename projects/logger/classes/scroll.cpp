#include NAMES_INCLUDE
#include SCROLL_INCLUDE_PATH

logger::codes logger::classic_scroll::vertical_drag(HWND hwnd, WPARAM wParam) {
    // Get all the vertial scroll bar information.
    SCROLLINFO si = {};
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    if (GetScrollInfo(hwnd, SB_VERT, &si) == FALSE) {
        throw le(codes::get_scroll_info_fail, get_scroll_info_fail_description);
    }

    // Save the position for comparison later on.
    m_vscroll_position = si.nPos;
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
    if (GetScrollInfo(hwnd, SB_VERT, &si) == FALSE) {
        throw le(codes::get_scroll_info_fail, get_scroll_info_fail_description);
    }

    // If the position has changed, scroll window and update it.
    if (si.nPos != m_vscroll_position)
    {
        if (ScrollWindow(hwnd, 0, m_yChar * (m_vscroll_position - si.nPos), NULL, NULL) == FALSE) {
            throw le(codes::scroll_window_fail, scroll_window_fail_description);
        }
    }

    return codes::success;
}

logger::codes logger::classic_scroll::horizontal_drag(HWND hwnd, WPARAM wParam) {
    SCROLLINFO si = {};
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    if (GetScrollInfo(hwnd, SB_HORZ, &si) == FALSE) {
        throw le(codes::get_scroll_info_fail, get_scroll_info_fail_description);
    }

    m_hscroll_position = si.nPos;
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

    // Ensure the position is within valid range.
    si.nPos = std::clamp(si.nPos, si.nMin, si.nMax);

    // Set the position and then retrieve it.  Due to adjustments
    // by Windows it may not be the same as the value set.
    si.fMask = SIF_POS;
    SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
    if (GetScrollInfo(hwnd, SB_HORZ, &si) == FALSE) {
        throw le(codes::get_scroll_info_fail, get_scroll_info_fail_description);
    }

    // If the position has changed, scroll the window.
    if (si.nPos != m_hscroll_position)
    {
        if (ScrollWindow(hwnd, m_xChar * (m_hscroll_position - si.nPos), 0, NULL, NULL) == FALSE) {
            throw le(codes::scroll_window_fail, scroll_window_fail_description);
        }

        if (InvalidateRect(hwnd, nullptr, TRUE) == FALSE) {
            throw le(codes::invalidate_rect_fail, invalidate_rect_fail_description);
        }

        if (UpdateWindow(hwnd) == FALSE) {
            throw le(codes::update_window_fail, update_window_fail_description);
        }
    }

    return codes::success;
}

logger::codes logger::classic_scroll::window_size_change(HWND hwnd, LPARAM lParam) {
    // Retrieve the dimensions of the client area. 
    m_yClient = HIWORD(lParam);
    m_xClient = LOWORD(lParam);

    SCROLLINFO si = {};

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
    si.nPage = m_xClient / m_xChar;;
    SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

    return codes::success;
}
