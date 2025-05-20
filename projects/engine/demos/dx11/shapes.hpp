/***********************************************
* File: shapes.hpp
*
* Purpose: some simple shapes rendering for demos
*
* Project: engine
*
************************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_DEPENDS_INCLUDE_PATH



// map size where 1 = 1 cube dimension
// so if the map size was 1x1x1 it would equal one cube
#define MAP_SIZE_X 1024.0f
#define MAP_SIZE_Y 1024.0f
#define MAP_SIZE_Z 1024.0f

// floating point scale factor 
#define SF_X 1.0f/MAP_SIZE_X
#define SF_Y 1.0f/MAP_SIZE_Y
#define SF_Z 1.0f/MAP_SIZE_Z


namespace engine {
	namespace dx11 {
		struct size_f {
			float szf_x, szf_y, szf_z;
		};

		struct size {
			std::size_t sz_x;
			std::size_t sz_y;
			std::size_t sz_z;

			// convert to gpu coordinates (floats)
			size_f convert_wc();
		};

		struct position {
			float x, y, z;
		};


		struct triangle {
			DirectX::XMFLOAT3 v1;
			DirectX::XMFLOAT3 v2;
			DirectX::XMFLOAT3 v3;
		};

		struct square {
			static const int size = 2;
			triangle faces[size];
		};

		struct cube {
			static const int size = 6;
			square faces[size];
		};
	}
}