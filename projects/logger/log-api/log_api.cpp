#include "log_api.hpp"
/***************************************
*  File: log_api.cpp (logger project helper 
*        functions)
*
*  Purpose: log_api.hpp definitions
*
*  Project: logger
* *************************************/

#include LOGGER_NAMES_INCLUDE
#include LOGGER_LOG_API_INCLUDE_PATH

std::wstring logger::to_wide_string(const char* narrow)
{
    /*

    std::size_t mbsrtowcs( wchar_t* dst,
                       const char** src,
                       std::size_t len,
                       std::mbstate_t* ps );

    dst 	- 	pointer to wide character array where the results will be stored
    src 	- 	pointer to pointer to the first element of a null-terminated multibyte string
    len 	- 	number of wide characters available in the array pointed to by dst
    ps 	- 	pointer to the conversion state object

    */

    // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    // get the length in bytes of "temp"
    std::size_t length = 1 + std::mbsrtowcs(nullptr, &narrow, 0, &state);

    // stack buffer
    wchar_t* buffer = nullptr;
    wchar_t stack_buffer[max_string_buffer];
    bool heap_allocated = false;

    // if length is greater than max_string_buffer, we will allocate a new buffer using new
    if (length > max_string_buffer) {
        buffer = new wchar_t[length];
        heap_allocated = true;
    }
    else {
        buffer = stack_buffer;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::mbsrtowcs(buffer, &narrow, length, &state);

    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {

        // clean up
        if (heap_allocated == true and buffer != nullptr) {
            delete[] buffer;
        }

        // throw an exception
        throw le(codes::to_wide_string_failed, to_wide_string_failed_description);

        // returns an empty string
        return {};
    }

    // clean up
    if (heap_allocated == true and buffer != nullptr) {
        std::wstring r_temp(buffer);
        delete[] buffer;
        return r_temp;
    }

    // return the wide string using the stack buffer
    return std::wstring(buffer);
}

std::wstring logger::to_wide_string(const std::string& narrow)
{
    /*

    std::size_t mbsrtowcs( wchar_t* dst,
                       const char** src,
                       std::size_t len,
                       std::mbstate_t* ps );

    dst 	- 	pointer to wide character array where the results will be stored
    src 	- 	pointer to pointer to the first element of a null-terminated multibyte string
    len 	- 	number of wide characters available in the array pointed to by dst
    ps 	- 	pointer to the conversion state object

    */

    // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    // temp in order to get the address of the pointer
    const char* temp = narrow.c_str();

    // get the length in bytes of "temp"
    std::size_t length = 1 + std::mbsrtowcs(nullptr, &temp, 0, &state);

    // stack buffer
    wchar_t* buffer = nullptr;
    wchar_t stack_buffer[max_string_buffer];
    bool heap_allocated = false;

    // if length is greater than max_string_buffer, we will allocate a new buffer using new
    if (length > max_string_buffer) {
        buffer = new wchar_t[length];
        heap_allocated = true;
    }
    else {
        buffer = stack_buffer;
    }

    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::mbsrtowcs(buffer, &temp, length, &state);

    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {

        // clean up
        if (heap_allocated == true and buffer != nullptr) {
            delete[] buffer;
        }

        // throw an exception
        throw le(codes::to_wide_string_failed, to_wide_string_failed_description);

        // returns an empty string
        return {};
    }

    // clean up
    if (heap_allocated == true and buffer != nullptr) {
        std::wstring r_temp(buffer);
        delete[] buffer;
        return r_temp;
    }

    // return the wide string using the buffer
    return std::wstring(buffer);
}

std::string logger::to_narrow_string(const wchar_t* wide)
{
    /*
    *
    Converts a sequence of wide characters from the array whose first element is pointed to by *src
    to its narrow multibyte representation that begins in the conversion state described by *ps.
    If dst is not null, converted characters are stored in the successive elements of the char array
    pointed to by dst. No more than len bytes are written to the destination array.


    std::size_t wcsrtombs( char* dst,
                       const wchar_t** src,
                       std::size_t len,
                       std::mbstate_t* ps );

    dst 	- 	pointer to narrow character array where the multibyte characters will be stored
    src 	- 	pointer to pointer to the first element of a null-terminated wide string
    len 	- 	number of bytes available in the array pointed to by dst
    ps 	    - 	pointer to the conversion state object

    */

    // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    // get the wide string length, does not include '\0'
    // returns the length in bytes
    std::size_t length = 1 + std::wcsrtombs(nullptr, &wide, 0, &state);

    // stack buffer
    char* buffer = nullptr;
    char stack_buffer[max_string_buffer];
    bool heap_allocated = false;

    // if length is greater than max_string_buffer, we will allocate a new buffer using new
    if (length > max_string_buffer) {
        buffer = new char[length];
        heap_allocated = true;
    }
    else {
        buffer = stack_buffer;
    }

    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::wcsrtombs(buffer, &wide, length, &state);


    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {

        // clean up
        if (heap_allocated == true and buffer != nullptr) {
            delete[] buffer;
        }

        // throw an exception
        throw le(codes::to_narrow_string_failed, to_narrow_string_failed_description);

        // returns an empty string
        return {};
    }

    // clean up
    if (heap_allocated == true and buffer != nullptr) {
        std::string r_temp(buffer);
        delete[] buffer;
        return r_temp;
    }

    // return the narrow string using the stack buffer
    return std::string(buffer);
}

std::string logger::to_narrow_string(const std::wstring& wide)
{
    /*
   *
   Converts a sequence of wide characters from the array whose first element is pointed to by *src
   to its narrow multibyte representation that begins in the conversion state described by *ps.
   If dst is not null, converted characters are stored in the successive elements of the char array
   pointed to by dst. No more than len bytes are written to the destination array.


   std::size_t wcsrtombs( char* dst,
                      const wchar_t** src,
                      std::size_t len,
                      std::mbstate_t* ps );

   dst 	- 	pointer to narrow character array where the multibyte characters will be stored
   src 	- 	pointer to pointer to the first element of a null-terminated wide string
   len 	- 	number of bytes available in the array pointed to by dst
   ps 	    - 	pointer to the conversion state object

   */

   // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    // get the wide string length, does not include '\0'
    // returns the length in bytes
    const wchar_t* temp = wide.c_str();
    std::size_t length = 1 + std::wcsrtombs(nullptr, &temp, 0, &state);

    // stack buffer
    char* buffer = nullptr;
    char stack_buffer[max_string_buffer];
    bool heap_allocated = false;

    // if length is greater than max_string_buffer, we will allocate a new buffer using new
    if (length > max_string_buffer) {
        buffer = new char[length];
        heap_allocated = true;
    }
    else {
        buffer = stack_buffer;
    }

    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */

    std::size_t error_code = std::wcsrtombs(buffer, &temp, length, &state);


    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {

        // clean up
        if (heap_allocated == true and buffer != nullptr) {
            delete[] buffer;
        }

        // throw an exception
        throw le(codes::to_narrow_string_failed, to_narrow_string_failed_description);

        // returns an empty string
        return {};
    }

    // clean up
    if (heap_allocated == true and buffer != nullptr) {
        std::string r_temp(buffer);
        delete[] buffer;
        return r_temp;
    }

    // return the narrow string using the stack buffer
    return std::string(buffer);
}

std::wstring logger::to_wide_string(const char* narrow, codes* code_p)
{
    // return nothing if code is nullptr
    if (code_p == nullptr) {
        return {};
    }


    /*

    std::size_t mbsrtowcs( wchar_t* dst,
                       const char** src,
                       std::size_t len,
                       std::mbstate_t* ps );

    dst 	- 	pointer to wide character array where the results will be stored
    src 	- 	pointer to pointer to the first element of a null-terminated multibyte string
    len 	- 	number of wide characters available in the array pointed to by dst
    ps 	- 	pointer to the conversion state object

    */

    // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    /*

    On success, returns the number of wide characters, excluding the terminating L'\0',
    written to the character array. If dst is a null pointer, returns the number of wide
    characters that would have been written given unlimited length.

    */
    std::size_t length = 1 + std::mbsrtowcs(nullptr, &narrow, 0, &state);


    wchar_t* buffer = nullptr;

    // stack buffer
    wchar_t stack_buffer[max_string_buffer];
    buffer = stack_buffer;
    bool heap_alloc = false;

    // if length is greater than max_string_buffer, we allocate memory:
    if (length > max_string_buffer) {
        buffer = new wchar_t[length];
        heap_alloc = true;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::mbsrtowcs(buffer, &narrow, length, &state);

    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
        *code_p = codes::to_wide_string_failed;

        if (heap_alloc and buffer != nullptr) {
            delete[] buffer;
        }

        // returns an empty string
        return {};
    }

    std::wstring temp_buffer(buffer);

    if (heap_alloc and buffer != nullptr) {
        delete[] buffer;
    }

    *code_p = codes::success;

    // return the wide string using the buffer
    return temp_buffer;
}

std::wstring logger::to_wide_string(const std::string& narrow, codes* code_p)
{
    // return nothing if code is nullptr
    if (code_p == nullptr) {
        return {};
    }


    /*

    std::size_t mbsrtowcs( wchar_t* dst,
                       const char** src,
                       std::size_t len,
                       std::mbstate_t* ps );

    dst 	- 	pointer to wide character array where the results will be stored
    src 	- 	pointer to pointer to the first element of a null-terminated multibyte string
    len 	- 	number of wide characters available in the array pointed to by dst
    ps 	- 	pointer to the conversion state object

    */

    // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    const char* temp = narrow.c_str();

    /*

    On success, returns the number of wide characters, excluding the terminating L'\0',
    written to the character array. If dst is a null pointer, returns the number of wide
    characters that would have been written given unlimited length.

    */
    std::size_t length = 1 + std::mbsrtowcs(nullptr, &temp, 0, &state);


    wchar_t* buffer = nullptr;

    // stack buffer
    wchar_t stack_buffer[max_string_buffer];
    buffer = stack_buffer;
    bool heap_alloc = false;

    // if length is greater than max_string_buffer, allocate more memory.
    if (length > max_string_buffer) {
        buffer = new wchar_t[length];
        heap_alloc = true;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::mbsrtowcs(buffer, &temp, length, &state);

    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
        *code_p = codes::to_wide_string_failed;

        if (heap_alloc and buffer != nullptr) {
            delete[] buffer;
        }

        // returns an empty string
        return {};
    }

    std::wstring temp_buffer(buffer);

    if (heap_alloc and buffer != nullptr) {
        delete[] buffer;
    }

    *code_p = codes::success;

    // return the wide string using the buffer
    return temp_buffer;
}

std::string logger::to_narrow_string(const wchar_t* wide, codes* code_p)
{
    // return nothing if code is nullptr
    if (code_p == nullptr) {
        return {};
    }


    /*
   *
   Converts a sequence of wide characters from the array whose first element is pointed to by *src
   to its narrow multibyte representation that begins in the conversion state described by *ps.
   If dst is not null, converted characters are stored in the successive elements of the char array
   pointed to by dst. No more than len bytes are written to the destination array.


   std::size_t wcsrtombs( char* dst,
                      const wchar_t** src,
                      std::size_t len,
                      std::mbstate_t* ps );

   dst 	- 	pointer to narrow character array where the multibyte characters will be stored
   src 	- 	pointer to pointer to the first element of a null-terminated wide string
   len 	- 	number of bytes available in the array pointed to by dst
   ps 	    - 	pointer to the conversion state object

   */

   // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    // get the wide string length, does not include '\0'
    // returns the length in bytes
    std::size_t length = 1 + std::wcsrtombs(nullptr, &wide, 0, &state);

    char* buffer = nullptr;
    char temp_buffer[max_string_buffer];
    bool heap_alloc = false;


    // if length is greater than max_string_buffer, we have an error:
    // use new to allocate memory to compensate 
    if (length > max_string_buffer) {
        buffer = new char[length];
        heap_alloc = true;
    }
    else {
        buffer = temp_buffer;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::wcsrtombs(buffer, &wide, length, &state);


    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
        *code_p = codes::to_narrow_string_failed;

        if (heap_alloc and buffer != nullptr) {
            delete[] buffer;
        }

        // returns an empty string
        return {};
    }

    std::string temp_buffer_str(buffer);

    if (heap_alloc and buffer != nullptr) {
        delete[] buffer;
    }

    *code_p = codes::success;

    // return the narrow string using the buffer
    return temp_buffer_str;
}

std::string logger::to_narrow_string(const std::wstring& wide, codes* code_p)
{
    // return nothing if code is nullptr
    if (code_p == nullptr) {
        return {};
    }


    /*
   *
   Converts a sequence of wide characters from the array whose first element is pointed to by *src
   to its narrow multibyte representation that begins in the conversion state described by *ps.
   If dst is not null, converted characters are stored in the successive elements of the char array
   pointed to by dst. No more than len bytes are written to the destination array.


   std::size_t wcsrtombs( char* dst,
                      const wchar_t** src,
                      std::size_t len,
                      std::mbstate_t* ps );

   dst 	- 	pointer to narrow character array where the multibyte characters will be stored
   src 	- 	pointer to pointer to the first element of a null-terminated wide string
   len 	- 	number of bytes available in the array pointed to by dst
   ps 	    - 	pointer to the conversion state object

   */

   // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    const wchar_t* temp = wide.c_str();

    // get the wide string length, does not include '\0'
    // returns the length in bytes
    std::size_t length = 1 + std::wcsrtombs(nullptr, &temp, 0, &state);

    char* buffer = nullptr;
    char temp_buffer[max_string_buffer];
    bool heap_alloc = false;


    // if length is greater than max_string_buffer, we have an error:
    // use new to allocate memory to compensate 
    if (length > max_string_buffer) {
        buffer = new char[length];
        heap_alloc = true;
    }
    else {
        buffer = temp_buffer;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::wcsrtombs(buffer, &temp, length, &state);


    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
        *code_p = codes::to_narrow_string_failed;

        if (heap_alloc and buffer != nullptr) {
            delete[] buffer;
        }

        // returns an empty string
        return {};
    }

    std::string temp_buffer_str(buffer);

    if (heap_alloc and buffer != nullptr) {
        delete[] buffer;
    }


    *code_p = codes::success;

    // return the narrow string using the buffer
    return temp_buffer_str;
}

logger::codes logger::vertical_drag(HWND hwnd, WPARAM wParam, int* vscroll_position, int yChar)
{
    // Get all the vertial scroll bar information.
    SCROLLINFO si = {};
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    if (GetScrollInfo(hwnd, SB_VERT, &si) == FALSE) {
        throw le(codes::get_scroll_info_fail, get_scroll_info_fail_description);
    }

    // Save the position for comparison later on.
    *vscroll_position = si.nPos;
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
    if (si.nPos != *vscroll_position)
    {
        if (ScrollWindow(hwnd, 0, yChar * (*vscroll_position - si.nPos), NULL, NULL) == FALSE) {
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

logger::codes logger::horizontal_drag(HWND hwnd, WPARAM wParam, int* hscroll_position,int xChar)
{
    SCROLLINFO si = {};
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    if (GetScrollInfo(hwnd, SB_HORZ, &si) == FALSE) {
        throw le(codes::get_scroll_info_fail, get_scroll_info_fail_description);
    }

    *hscroll_position = si.nPos;
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
    if (si.nPos != *hscroll_position)
    {
        if (ScrollWindow(hwnd, xChar * (*hscroll_position - si.nPos), 0, NULL, NULL) == FALSE) {
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

logger::codes logger::window_size_change(HWND hwnd, LPARAM lParam, int nol, int yChar, int xChar, int xClientMax)
{
    if (yChar==0 or xChar==0) {
        return codes::divison_by_zero;
    }
    
    
    // Retrieve the dimensions of the client area. 
    int yClient = HIWORD(lParam);
    int xClient = LOWORD(lParam);

    {
        SCROLLINFO si = {};

        // Set the vertical scrolling range and page size
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_PAGE;
        si.nMin = 0;
        si.nMax = nol - 1;
        si.nPage = yClient / yChar;
        SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
    }


    {
        SCROLLINFO si = {};

        // Set the horizontal scrolling range and page size. 
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_PAGE;
        si.nMin = 0;
        si.nMax = 2 + xClientMax / xChar;
        si.nPage = xClient / xChar;
        SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
    }

    return codes::success;
}

logger::codes logger::send_text(HWND window, const string* message, RECT* position)
{
    // win32 api function
    /*
    
    int DrawText(
      [in]      HDC     hdc,
      [in, out] LPCTSTR lpchText,
      [in]      int     cchText,
      [in, out] LPRECT  lprc,
      [in]      UINT    format
    );
    
    */
    if (message == nullptr or position == nullptr) {
        return logger::codes::pointer_is_nullptr;
    }

    if (window == nullptr) {
        return codes::hwnd_error;
    }

    HDC hdc = GetDC(window);

    if (hdc == nullptr) {
        return codes::hdc_error;
    }

    int text_height = DrawText(hdc, message->c_str(), -1, position, NULL);
    
    ReleaseDC(window, hdc);

    return (text_height > 0) ? codes::success : codes::draw_text_error;
}

logger::codes logger::send_text(HDC hdc,const string* message, RECT* position)
{
    // win32 api function
    /*

    int DrawText(
      [in]      HDC     hdc,
      [in, out] LPCTSTR lpchText,
      [in]      int     cchText,
      [in, out] LPRECT  lprc,
      [in]      UINT    format
    );

    */

    if (hdc == nullptr) {
        return codes::hdc_error;
    }

    if (message == nullptr or position == nullptr) {
        return logger::codes::pointer_is_nullptr;
    }

    int text_height = DrawText(hdc, message->c_str(), -1, position, NULL);

    return (text_height > 0) ? codes::success : codes::draw_text_error;
}

logger::string logger::time_stamped(const string& message)
{
    try {
        auto now = std::chrono::system_clock::now();
        string time = std::format(ROS("[{}]"), now);
        return time + message;
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "unknown exception caught..." << std::endl;
    }
    // exception thrown we return nothing
    return {};
}

void logger::er_co_out(codes code)
{
    string description = le::match_code(code);
    le log_out(code, description);
    CERROR << log_out.m_desc << "\n" << log_out.m_loc << "\n" << log_out.m_w32 << std::endl;
}

std::size_t logger::count_new_lines(const string& message)
{
    std::size_t new_line_counter = 0;
    for (auto c : message) {
        if (c == '\n') {
            new_line_counter++;
        }
    }
    return new_line_counter;
}

std::size_t logger::calculate_logs_to_print(std::vector<log*>* vl_p, std::size_t s_index, std::size_t window_height)
{
    if (vl_p == nullptr) {
        throw le(logger::codes::pointer_is_nullptr, pointer_is_nullptr_description);
    }

    if (s_index > vl_p->size()) {
        throw le(logger::codes::index_out_of_range, index_out_of_range_description);
    }

    std::size_t line_counter = 0;
    std::size_t max_bottom = 0;
    std::size_t single_lines = window_height / (LOGGER_FONT_SIZE + 2) + s_index;
    for (std::size_t i = s_index; i < single_lines and i < vl_p->size(); ++i) {
        auto log = vl_p->at(i);

        if (log->message->empty()) {
            break;
        }

        // add up bottoms until its greater than window_height
        max_bottom += log->window_position->bottom;

        line_counter++;

        if (max_bottom >= window_height) {
            break;
        }
    }

    if (max_bottom > window_height) {
        // go back one line
        line_counter--;
    }

    return line_counter;
}

void logger::build_rects(std::vector<log*>* vl_p, std::size_t s_index, std::size_t e_index, RECT* window)
{
    if (vl_p == nullptr or window == nullptr) {
        throw le(logger::codes::pointer_is_nullptr, pointer_is_nullptr_description);
    }

    if (s_index > vl_p->size() or e_index > vl_p->size()) {
        throw le(logger::codes::index_out_of_range, index_out_of_range_description);
    }

    RECT last = {};
    for (std::size_t i = s_index; i < e_index; ++i) {
        auto log = vl_p->at(i);

        if (log->message->empty()) {
            break;
        }

        std::size_t total_lines = count_new_lines(*log->message) + 1;

        std::size_t height = total_lines * (LOGGER_FONT_SIZE + 2);

        last = RECT(window->left, window->top + last.bottom, window->right,last.bottom + height);

        *log->window_position = last;
    }
}
