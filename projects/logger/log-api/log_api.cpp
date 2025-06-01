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

