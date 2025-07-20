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
		
		class ENGINE_API physics {
		public:
			physics() {};
			
			void update(float dt);
		protected:
			const float m_gravity = 10.0f;
			
			float m_momentum = 0.0f;
			float m_force = 0.0f;
			float m_acceleration = 0.0f;
			float m_velocity = 0.0f;

			std::vector<DirectX::XMFLOAT3> x_move(float x, const std::vector<DirectX::XMFLOAT3>& v);
			std::vector<DirectX::XMFLOAT3> y_move(float y, const std::vector<DirectX::XMFLOAT3>& v);
			std::vector<DirectX::XMFLOAT3> z_move(float z, const std::vector<DirectX::XMFLOAT3>& v);

			std::vector<DirectX::XMFLOAT3> move(DirectX::XMFLOAT3 direction, const std::vector<DirectX::XMFLOAT3>& vertices);
		};
	}
}