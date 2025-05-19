/***************************************
*  File: names.hpp
*
*  Purpose: easy file name changes and moves
*			within engine project
*
*  Project: engine
* *************************************/

// dependencies
#define ENGINE_STL_PRIVATE_INCLUDE_PATH				ENGINE_stl_includes_hpp					// the entire stl library
#define ENGINE_WIN_INCLUDE_PATH						ENGINE_win_hpp							// all windows includes
#define ENGINE_STL_INCLUDE_PATH						ENGINE_stl_hpp							// specific version include stl library
#define ENGINE_TYPES_INCLUDE_PATH					ENGINE_types_hpp						// types stuff
#define ENGINE_DX_INCLUDE_PATH						ENGINE_dx_api_inc_hpp					// direct x includes

// all dependencies include
#define ENGINE_ALL_DEPENDS_INCLUDE_PATH				ENGINE_d_inc_hpp						// includes all dependencies in one header

// all engine library
#define ENGINE_ALL_ENGINE_INCLUDE_PATH				ENGINE_all_engine_hpp					// includes all engine headers

// classes
#define ENGINE_DX11CAM_INCLUDE_PATH					ENGINE_dx11_camera_hpp					// direct x 11 camera
#define ENGINE_DX11SETUP_INCLUDE_PATH				ENGINE_sdx11_hpp						// direct x 11 setup

// error
#define ENGINE_CODES_INCLUDE_PATH					ENGINE_codes_hpp						// error codes
#define ENGINE_DX11ERU_INCLUDE_PATH					ENGINE_e_dx11_u_hpp						// direct x 11 error utilities
#define ENGINE_CO_INCLUDE_PATH						ENGINE_co_hpp							// code object
#define ENGINE_CD_INCLUDE_PATH						ENGINE_desc_hpp							// error code descriptions

// api helper
#define ENGINE_API_INCLUDE_PATH						ENGINE_engine_api_hpp					// helper functions