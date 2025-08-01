/***************************************
*  File: engine_api.hpp
*
*  Purpose: helper functions
*
*  Project: engine
* *************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_DEPENDS_INCLUDE_PATH
#include ENGINE_CO_INCLUDE_PATH
#include ENGINE_DX11_DEMO_SHAPES_INCLUDE_PATH

// logger lib
#include LOGGER_NAMES_INCLUDE
#include LOGGER_ALL_LOGS_INCLUDE_PATH

namespace engine {
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

	// gets the location of the caller function
	string ENGINE_API gl(std::source_location sl = std::source_location::current());

	// outputs the code message
	void ENGINE_API output_code(codes code,const string& location = gl());

	// matches a code to a description
	string match_code(codes code);

	// send data to terminal
	// depends on macro definitions which terminal
	// see macro/types.hpp
	void ENGINE_API output_co(const engine::ee& e);


	// simple drawing functions {

	// create a cube from a position and size
	dx11::cube create_cube(dx11::size sz, dx11::position p);

	// cube to vertex buffer, organizes a cube to be read as a vertex buffer
	std::vector<DirectX::XMFLOAT3> cube_to_vb(const dx11::cube& cb);

	// }


	std::vector<DirectX::XMFLOAT3> x_move(float x, const std::vector<DirectX::XMFLOAT3>& v);
	std::vector<DirectX::XMFLOAT3> y_move(float y, const std::vector<DirectX::XMFLOAT3>& v);
	std::vector<DirectX::XMFLOAT3> z_move(float z, const std::vector<DirectX::XMFLOAT3>& v);

	std::vector<DirectX::XMFLOAT3> move(DirectX::XMFLOAT3 direction, const std::vector<DirectX::XMFLOAT3>& vertices);

	bool mouse_collide(float x, float y, const std::vector<DirectX::XMFLOAT3>& vertices);

	UINT get_window_width(HWND handle);
	UINT get_window_height(HWND handle);
}