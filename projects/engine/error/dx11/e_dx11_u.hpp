/***********************************************
* File: e_dx11_u.hpp (errors direct x 11 utilities)
*
* Purpose: helper functions for dx11 errors
*
* Project: engine
*
************************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_DEPENDS_INCLUDE_PATH
#include ENGINE_CODES_INCLUDE_PATH


namespace engine {
	namespace dx11 {
		// translate a ID3D11InfoQueue* to a string
		string debug_info_ts(ID3D11InfoQueue* debug_info_p, codes* code);

		// translate a blob error to string
		string error_blob_ts(ID3DBlob* error, codes* code);

		// translate an hresult code to a string 
		string hr_ts(HRESULT hr);

		// send to visual studio output window
		void st_vs_out(HRESULT hr, string location = lb::get_location());
	}
}