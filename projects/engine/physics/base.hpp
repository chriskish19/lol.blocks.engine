/***************************************
*  File: base.hpp
*
*  Purpose: foundation for physics
*
*  Project: engine
* *************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_DEPENDS_INCLUDE_PATH

namespace engine {
	namespace dx11 {
		struct CubePhysicsData {
			DirectX::XMFLOAT3 position;   // xyz = position
			DirectX::XMFLOAT3 velocity;   // xyz = velocity
		};

		std::vector<CubePhysicsData> find_new_position(float dt, float mass, float velocity);


		class ENGINE_API base_physics {
		public:
			base_physics() {};
			
			void update(float dt);
		protected:


			std::vector<CubePhysicsData> m_data;
		};
	}
}