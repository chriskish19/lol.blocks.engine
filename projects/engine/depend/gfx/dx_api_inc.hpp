/***********************************************
* File: dx_api_inc.hpp (direct x api includes)
*
* Purpose: enables use of direct x
*
*
*
************************************************/

#pragma once


// basic directx infrastucture
#include <dxgi.h>

// compiler header for interpreting hlsl
#include <d3dcompiler.h> 

// support for microsoft comptr
#include <wrl.h>

// math
#include <DirectXMath.h>

// directx 11 header
#include <d3d11.h>

// directx12 header
#include <d3d12.h>



// dx toolkit 
// {

// for DDS textures
#include <DDSTextureLoader.h> 

// for PNG, JPEG, BMP, etc.
#include <WICTextureLoader.h>  

// sprites
#include <DirectXTK/SpriteBatch.h>

// dx keyboard
#include <DirectXTK/Keyboard.h>

// mouse movement
#include <Mouse.h>

// ??
#include <DirectXTK/CommonStates.h>

// }