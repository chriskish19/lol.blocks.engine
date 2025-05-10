
/***************************************
*  File: co.cpp (code object)
*
*  Purpose: co.hpp definitions
*
*  Project: logger
* *************************************/

#include LOGGER_NAMES_INCLUDE
#include LOGGER_CO_INCLUDE_PATH

logger::string logger::gl(std::source_location sl)
{
    std::string function_name = sl.function_name();
    std::string line = std::to_string(sl.line());
    std::string column = std::to_string(sl.column());
    std::string file_name = sl.file_name();

    std::string temp = std::format("File name: {} \n - column: {} \n - line: {} \n - function name: {} \n",
        file_name, column, line, function_name);

#if WIDE
    // convert to wide string
    std::wstring wide_return = le::to_wide(temp);
    return wide_return;
#else
    return temp;
#endif
}


std::wstring logger::le::to_wide(const std::string& narrow)
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
    wchar_t stack_buffer[MAX_STRING];
    bool heap_allocated = false;

    // if length is greater than max_string_buffer, we will allocate a new buffer using new
    if (length > MAX_STRING) {
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

        // throw an exception, werid to throw an object inside the object but were inside 
        // a static function so...
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

logger::string logger::le::get_w32_error()
{
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0)
        return ROS("No windows error."); // No error has occurred

    character_p messageBuffer = nullptr;

    // Format the error message from the system
    size_t size = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, errorMessageID,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (character_p)&messageBuffer, 0, nullptr);

    string message(messageBuffer, size);

    // Free the buffer allocated by FormatMessage
    LocalFree(messageBuffer);

    return message;
}

logger::string logger::le::match_code(codes code)
{
    switch (code) {
        case codes::success:
            success_description;
        case codes::uninitialized:
            uninitialized_description;
        case codes::register_class_fail:
            register_class_fail_description;
        case codes::hwnd_error:
            hwnd_error_description;
        case codes::to_wide_string_failed:
            to_wide_string_failed_description;
        case codes::get_client_rect_fail:
            get_client_rect_fail_description;
        case codes::module_handle_error:
            module_handle_error_description;
        case codes::get_scroll_info_fail:
            get_scroll_info_fail_description;
        case codes::scroll_window_fail:
            scroll_window_fail_description;
        case codes::invalidate_rect_fail:
            invalidate_rect_fail_description;
        case codes::update_window_fail:
            update_window_fail_description;
        case codes::to_narrow_string_failed:
            to_narrow_string_failed_description;
        case codes::hdc_error:
            hdc_error_description;
        case codes::draw_text_error:
            draw_text_error_description;
        case codes::write_to_file_error:
            write_to_file_error_description;
        case codes::file_open_error:
            file_open_error_description;
        case codes::font_nullptr:
            font_nullptr_description;
        case codes::get_text_metrics_fail:
            get_text_metrics_fail_description;
        default:
            return default_match_code_description;
    }
}
