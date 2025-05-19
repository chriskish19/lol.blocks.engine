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

#include <DDSTextureLoader.h>	// for DDS textures
#include <WICTextureLoader.h>	// for PNG, JPEG, BMP, etc. 
#include <SpriteBatch.h>		// sprites
#include <Keyboard.h>			// dx keyboard
#include <Mouse.h>				// mouse movement
#include <SimpleMath.h>         // Optional: Simplified math wrapper around DirectX::XMMATRIX etc.
#include <SpriteFont.h>         // For 2D text rendering
#include <PrimitiveBatch.h>     // For drawing lines and shapes
#include <GeometricPrimitive.h> // For built-in 3D shapes
#include <Model.h>              // For loading/rendering .CMO or .VBO models
#include <Effects.h>            // Common effects (basic lighting, fog, etc.)
#include <CommonStates.h>       // Predefined blend, rasterizer, depth-stencil states


// }