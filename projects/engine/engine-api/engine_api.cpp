#include "engine_api.hpp"
/***************************************
*  File: engine_api.cpp
*
*  Purpose: engine_api.hpp definitions
*
*  Project: engine
* *************************************/

#include ENGINE_NAMES_INCLUDE
#include ENGINE_API_INCLUDE_PATH


std::wstring engine::to_wide_string(const char* narrow)
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
        throw ee(codes::to_wide_string_failed, to_wide_string_failed_description);

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

std::wstring engine::to_wide_string(const std::string& narrow)
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
        throw ee(codes::to_wide_string_failed, to_wide_string_failed_description);

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

std::string engine::to_narrow_string(const wchar_t* wide)
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
        throw ee(codes::to_narrow_string_failed, to_narrow_string_failed_description);

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

std::string engine::to_narrow_string(const std::wstring& wide)
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
        throw ee(codes::to_narrow_string_failed, to_narrow_string_failed_description);

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

std::wstring engine::to_wide_string(const char* narrow, codes* code_p)
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

std::wstring engine::to_wide_string(const std::string& narrow, codes* code_p)
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

std::string engine::to_narrow_string(const wchar_t* wide, codes* code_p)
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

std::string engine::to_narrow_string(const std::wstring& wide, codes* code_p)
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

void engine::output_code(codes code, const string& location)
{
#if !ALL_CODES_LOGGED
    if (code == codes::success) {
        return;
    }
#endif  

    logger::string message = engine::match_code(code);
#if SYS_LOG_OUT
    logger::glb_sl->log_message(message + ROS('\n') + ROS("LOCATION: ") + location);
#endif
#if STD_COUT
    COUT << message << '\n' << ROS("LOCATION: ") << location;
#endif
#if VS_OUT_WINDOW
    message = message + "\n" + location;
    OutputDebugString(message.c_str());
#endif
}

engine::string engine::match_code(codes code)
{
    switch (code) {
    case codes::success:
        return success_description;
    case codes::uninitialized:
        return uninitialized_description;
    case codes::to_narrow_string_failed:
        return to_narrow_string_failed_description;
    case codes::to_wide_string_failed:
        return to_wide_string_failed_description;
    case codes::pointer_is_nullptr:
        return pointer_is_nullptr_description;
    default:
        return default_match_code_description;
    }
}

void engine::output_co(const engine::ee& e)
{
#if SYS_LOG_OUT
    logger::glb_sl->log_message(e.m_desc + ROS('\n') + ROS("LOCATION: ") + e.m_loc);
#endif
#if STD_COUT
    COUT << e.m_desc << '\n' << ROS("LOCATION: ") << e.m_loc;
#endif
#if VS_OUT_WINDOW
    string message;
    message = e.m_desc + ROS('\n') + ROS("LOCATION: ") + e.m_loc;
    OutputDebugString(message.c_str());
#endif
}

engine::dx11::cube engine::create_cube(dx11::size sz, dx11::position p)
{
    engine::dx11::size_f wc = sz.convert_wc();
    engine::dx11::cube cb = {};

    float x = p.x;
    float y = p.y;
    float z = p.z;

    float sx = wc.szf_x;
    float sy = wc.szf_y;
    float szf = wc.szf_z;

    // Define 8 corners of the cube
    DirectX::XMFLOAT3 v000(x, y, z);                    // front top left
    DirectX::XMFLOAT3 v001(x, y, z + szf);              // back top left
    DirectX::XMFLOAT3 v010(x, y - sy, z);               // front bottom left
    DirectX::XMFLOAT3 v011(x, y - sy, z + szf);         // back bottom left
    DirectX::XMFLOAT3 v100(x + sx, y, z);               // front top right
    DirectX::XMFLOAT3 v101(x + sx, y, z + szf);         // back top right
    DirectX::XMFLOAT3 v110(x + sx, y - sy, z);          // front bottom right
    DirectX::XMFLOAT3 v111(x + sx, y - sy, z + szf);    // back bottom right

    // Front face (z)
    cb.faces[0].faces[0] = { v000, v010, v100 };
    cb.faces[0].faces[1] = { v100, v010, v110 };

    // Back face (-z)
    cb.faces[1].faces[0] = { v101, v111, v001 };
    cb.faces[1].faces[1] = { v001, v111, v011 };

    // Left face (-x)
    cb.faces[2].faces[0] = { v001, v011, v000 };
    cb.faces[2].faces[1] = { v000, v011, v010 };

    // Right face (+x)
    cb.faces[3].faces[0] = { v100, v110, v101 };
    cb.faces[3].faces[1] = { v101, v110, v111 };

    // Top face (+y)
    cb.faces[4].faces[0] = { v000, v100, v001 };
    cb.faces[4].faces[1] = { v001, v100, v101 };

    // Bottom face (-y)
    cb.faces[5].faces[0] = { v010, v011, v110 };
    cb.faces[5].faces[1] = { v110, v011, v111 };

    return cb;
}

std::vector<DirectX::XMFLOAT3> engine::cube_to_vb(const dx11::cube& cb)
{
    std::vector<DirectX::XMFLOAT3> vertices;

    for (int face = 0; face < engine::dx11::cube::size; ++face) {
        for (int tri = 0; tri < engine::dx11::square::size; ++tri) {
            const auto& t = cb.faces[face].faces[tri];
            vertices.push_back(t.v1);
            vertices.push_back(t.v2);
            vertices.push_back(t.v3);
        }
    }

    return vertices;
}

engine::string engine::gl(std::source_location sl)
{
    std::string function_name = sl.function_name();
    std::string line = std::to_string(sl.line());
    std::string column = std::to_string(sl.column());
    std::string file_name = sl.file_name();

    std::string temp = std::format("File name: {} \n - column: {} \n - line: {} \n - function name: {} \n",
        file_name, column, line, function_name);

#if WIDE
    // convert to wide string
    engine::codes code;
    std::wstring wide_return = to_wide_string(temp,&code);
    return wide_return;
#else
    return temp;
#endif
}

std::vector<DirectX::XMFLOAT3> engine::x_move(float x, const std::vector<DirectX::XMFLOAT3>& v)
{
    std::vector<DirectX::XMFLOAT3> result;
    result.reserve(v.size());
    for (const auto& pos : v) {
        result.emplace_back(pos.x + x, pos.y, pos.z);
    }
    return result;
}

std::vector<DirectX::XMFLOAT3> engine::y_move(float y, const std::vector<DirectX::XMFLOAT3>& v)
{
    std::vector<DirectX::XMFLOAT3> result;
    result.reserve(v.size());
    for (const auto& pos : v) {
        result.emplace_back(pos.x, pos.y + y, pos.z);
    }
    return result;
}

std::vector<DirectX::XMFLOAT3> engine::z_move(float z, const std::vector<DirectX::XMFLOAT3>& v)
{
    std::vector<DirectX::XMFLOAT3> result;
    result.reserve(v.size());
    for (const auto& pos : v) {
        result.emplace_back(pos.x, pos.y, pos.z + z);
    }
    return result;
}

std::vector<DirectX::XMFLOAT3> engine::move(DirectX::XMFLOAT3 direction, const std::vector<DirectX::XMFLOAT3>& vertices)
{
    std::vector<DirectX::XMFLOAT3> result;
    result.reserve(vertices.size());
    for (const auto& pos : vertices) {
        result.emplace_back(pos.x + direction.x, pos.y + direction.y, pos.z + direction.z);
    }
    return result;
}

bool engine::mouse_collide(float x, float y, const std::vector<DirectX::XMFLOAT3>& vertices)
{
    for (const auto& pos : vertices) {
        if (pos.x == x and pos.y == y) {
            return true;
        }
    }
    return false;
}

UINT engine::get_window_width(HWND handle)
{
    RECT window_rect;
    if (GetClientRect(handle, &window_rect) == FALSE) {
        throw ee(codes::client_rect_fail, client_rect_fail_description);
    }
    return window_rect.right - window_rect.left;
}

UINT engine::get_window_height(HWND handle)
{
    RECT window_rect;
    if (GetClientRect(handle, &window_rect) == FALSE) {
        throw ee(codes::client_rect_fail, client_rect_fail_description);
    }
    return window_rect.bottom - window_rect.top;
}
