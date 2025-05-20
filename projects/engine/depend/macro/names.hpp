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




// dx11 demo {

#define ENGINE_DX11_DEMO_INCLUDE_PATH						ENGINE_dx11_d_hpp						// all dx11 demos
#define ENGINE_DX11_DEMO_SHAPES_INCLUDE_PATH				ENGINE_shapes_hpp						// simple shape drawing

// dx11 demo shaders
#define ENGINE_TDDX11VS_FILE_PATH							ENGINE_td_dx11_vs_hlsl					// (triangle demo direct x 11 vertex shader)
#define ENGINE_TDDX11PS_FILE_PATH							ENGINE_td_dx11_ps_hlsl					// (triangle demo direct x 11 pixel shader)
#define ENGINE_TXDDX11VS_FILE_PATH							ENGINE_txd_dx11_vs_hlsl					// (texture demo direct x 11 vertex shader)
#define ENGINE_TXDDX11PS_FILE_PATH							ENGINE_txd_dx11_ps_hlsl					// (texture demo direct x 11 pixel shader)
#define ENGINE_CDDX11VS_FILE_PATH							ENGINE_cd_dx11_vs_hlsl					// (camera demo direct x 11 vertex shader)
#define ENGINE_CDDX11PS_FILE_PATH							ENGINE_cd_dx11_ps_hlsl					// (camera demo direct x 11 pixel shader)
#define ENGINE_CBDDX11VS_FILE_PATH							ENGINE_cbd_dx11_vs_hlsl					// (cube demo direct x 11 vertex shader)
#define ENGINE_CBDDX11PS_FILE_PATH							ENGINE_cbd_dx11_ps_hlsl					// (cube demo direct x 11 pixel shader)

// dx11 demo textures
#define ENGINE_TX_GRAPH										ENGINE_graph_png
#define ENGINE_TX_STICK										ENGINE_stick_png						// stickman sprite

// }