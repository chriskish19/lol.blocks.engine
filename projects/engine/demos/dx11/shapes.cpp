/***************************************
*  File: shapes.cpp
*
*  Purpose: shapes.hpp definitions
*
*  Project: engine
* *************************************/


#include ENGINE_NAMES_INCLUDE
#include ENGINE_DX11_DEMO_SHAPES_INCLUDE_PATH

engine::dx11::size_f engine::dx11::size::convert_wc()
{
    // multiply by scaling factor
    size_f wc = {};
    wc.szf_x = static_cast<float>(sz_x * (SF_X));
    wc.szf_y = static_cast<float>(sz_y * (SF_Y));
    wc.szf_z = static_cast<float>(sz_z * (SF_Z));

    return wc;
}
