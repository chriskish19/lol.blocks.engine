/***********************************************
* File: lol_dx11_d.hpp ( direct x 11 demo)
*
* Purpose: render graphics to the screen
*
* Used: 
*
************************************************/

#pragma once
#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_DEPENDS_INCLUDE_PATH
#include ENGINE_DX11ERU_INCLUDE_PATH
#include ENGINE_DX11SETUP_INCLUDE_PATH
#include ENGINE_DX11CAM_INCLUDE_PATH
#include ENGINE_API_INCLUDE_PATH
#include ENGINE_DX11_DEMO_SHAPES_INCLUDE_PATH
#include ENGINE_BASE_PHYSICS_INCLUDE_PATH



// logging library
#include LOGGER_NAMES_INCLUDE
#include LOGGER_ALL_LOGS_INCLUDE_PATH


namespace engine {
	namespace dx11 {

		// renders a single triangle
		class ENGINE_API triangle_demo {
		public:
			triangle_demo(HWND handle, UINT width, UINT height);
			~triangle_demo();


			codes load_content();
			void unload_content();
			void update(float dt);
			void render();


		protected:
			// solid color vertex shader
			ID3D11VertexShader* m_sc_vs = nullptr;

			// solid color pixel shader
			ID3D11PixelShader* m_sc_ps = nullptr;

			// input layout
			ID3D11InputLayout* m_il = nullptr;

			// vertex buffer blob
			ID3DBlob* m_vsb = nullptr;

			// main struct for dx11 pointers
			device_description* m_p_dd = new device_description{};

			// render target view
			ID3D11RenderTargetView* m_p_rtv = nullptr;

			// pixel shader blob
			ID3DBlob* m_psb = nullptr;


			struct VertexPos
			{
				DirectX::XMFLOAT3 pos;
			};

			// vertex buffer
			ID3D11Buffer* m_vb = nullptr;
		};



		// renders a texture to the screen
		class ENGINE_API texture_demo {
		public:
			texture_demo(HWND handle, UINT width, UINT height);
			~texture_demo();

			codes load_content();
			void unload_content();
			void update(float dt);
			void render();



		protected:
			// color map vertex shader
			ID3D11VertexShader* m_cm_vs = nullptr;

			// color map pixel shader
			ID3D11PixelShader* m_cm_ps = nullptr;

			// input layout
			ID3D11InputLayout* m_il = nullptr;

			// vertex buffer blob
			ID3DBlob* m_vsb = nullptr;

			// main struct for dx11 pointers
			device_description* m_p_dd = new device_description{};

			// render target view
			ID3D11RenderTargetView* m_p_rtv = nullptr;

			// pixel shader blob
			ID3DBlob* m_psb = nullptr;

			// vertex buffer
			ID3D11Buffer* m_vb = nullptr;

			// texture
			ID3D11ShaderResourceView* m_tx = nullptr;

			// color map sampler
			ID3D11SamplerState* m_cms = nullptr;

			struct VertexPos
			{
				DirectX::XMFLOAT3 pos;
				DirectX::XMFLOAT2 tex0;
			};

		};

		// simple texture demo
		class ENGINE_API simple_tx_demo {
		public:
			simple_tx_demo(HWND handle, UINT width, UINT height);
			~simple_tx_demo();

			codes load_content();
			void unload_content();
			void update(float dt);
			void render();

		protected:

			// main struct for dx11 pointers
			device_description* m_p_dd = new device_description{};

			// texture view
			ID3D11ShaderResourceView* m_tx = nullptr;

			// sprite
			DirectX::SpriteBatch* m_sb = nullptr;

			// render target view (back buffer)
			ID3D11RenderTargetView* m_p_rtv = nullptr;
		};

		// simple sprite animation demo
		class ss_demo {
		public:
			ss_demo(HWND handle, UINT width, UINT height);
			~ss_demo();

			codes load_content();
			void unload_content();
			void update(float dt);
			void render();


		protected:

			// main struct for dx11 pointers
			device_description* m_p_dd = new device_description{};

			// texture view
			ID3D11ShaderResourceView* m_tx = nullptr;

			// sprite
			DirectX::SpriteBatch* m_sb = nullptr;

			// render target view (back buffer)
			ID3D11RenderTargetView* m_p_rtv = nullptr;

			float moveSpeed = 100.0f; // pixels per second
			DirectX::XMFLOAT2 characterPos = { 100.0f, 100.0f }; // Starting position
			int currentFrame = 0;
			float frameTime = 0.1f; // seconds per frame
			float timeSinceLastFrame = 0.0f;
			const int totalFrames = 4;
			const int frameWidth = 32;
			const int frameHeight = 32;

			// key presses
			DirectX::Keyboard* m_kbd = nullptr;

			// blending
			DirectX::CommonStates* m_cs = nullptr;
		};



		class ENGINE_API camera_demo {
		public:
			camera_demo(HWND handle, UINT width, UINT height);
			~camera_demo();

			codes load_content();
			void unload_content();
			void update(float dt);
			void render();

		protected:
			// solid color vertex shader
			ID3D11VertexShader* m_sc_vs = nullptr;

			// solid color pixel shader
			ID3D11PixelShader* m_sc_ps = nullptr;

			// input layout
			ID3D11InputLayout* m_il = nullptr;

			// vertex buffer blob
			ID3DBlob* m_vsb = nullptr;

			// main struct for dx11 pointers
			device_description* m_p_dd = new device_description{};

			// render target view
			ID3D11RenderTargetView* m_p_rtv = nullptr;

			// pixel shader blob
			ID3DBlob* m_psb = nullptr;


			struct VertexPos
			{
				DirectX::XMFLOAT3 pos;
			};

			// vertex buffer
			ID3D11Buffer* m_vb = nullptr;

			// camera instance is default init'd
			Camera m_cam;

			struct CameraBuffer
			{
				DirectX::XMMATRIX view;
				DirectX::XMMATRIX projection;
			};

			// camera constant buffer gpu side
			ID3D11Buffer* m_cameraCB = nullptr;


			float moveSpeed = 10.0f; // pixels per second

			// key presses
			DirectX::Keyboard* m_kbd = nullptr;
		};



		class ENGINE_API cube_demo{
		public:
			cube_demo(HWND handle, UINT width, UINT height);
			~cube_demo();

			codes load_content();
			void unload_content();
			virtual void update(float dt);
			virtual void render();
		protected:
			// solid color vertex shader
			ID3D11VertexShader* m_sc_vs = nullptr;

			// solid color pixel shader
			ID3D11PixelShader* m_sc_ps = nullptr;

			// input layout
			ID3D11InputLayout* m_il = nullptr;

			// vertex buffer blob
			ID3DBlob* m_vsb = nullptr;

			// main struct for dx11 pointers
			device_description* m_p_dd = new device_description{};

			// render target view
			ID3D11RenderTargetView* m_p_rtv = nullptr;

			// pixel shader blob
			ID3DBlob* m_psb = nullptr;

			// vertex buffer
			ID3D11Buffer* m_vb = nullptr;

			std::vector<DirectX::XMFLOAT3> m_cube_vertices;

			// camera instance is default init'd
			Camera m_cam;

			struct CameraBuffer
			{
				DirectX::XMMATRIX view;
				DirectX::XMMATRIX projection;
				DirectX::XMMATRIX world;
			};

			// camera constant buffer gpu side
			ID3D11Buffer* m_cameraCB = nullptr;

			float sensitivity = 0.005f; // mouse sensitivity
			float moveSpeed = 10.0f; // pixels per second

			// key presses
			DirectX::Keyboard* m_kbd = nullptr;

			// mouse movement
			DirectX::Mouse* m_ms = nullptr;

			// for mouse cursor switch states
			// (switch mouse mode)
			bool m_smm = false;

			struct TimeBufferType
			{
				float gTime;
				float padding[3]; // Padding to align to 16 bytes (required by HLSL constant buffer rules)
			};

			ID3D11Buffer* m_timeBuffer = nullptr;

			float m_rotationAngle = 0.0f;

			TimeBufferType m_timeData = {};

			std::shared_ptr<DirectX::EffectFactory> m_fxFactory;

			std::unique_ptr<DirectX::DX11::Model> m_datson_model;
			std::unique_ptr<DirectX::DX11::Model> m_terrain_model;

			std::unique_ptr<DirectX::CommonStates> m_common_states;

			ID3D11DepthStencilView* m_p_dsv = nullptr;

			UINT m_width;
			UINT m_height;
			HWND m_handle;
		};

		class ENGINE_API cube_physics : public cube_demo , public physics{
		public:
			cube_physics(HWND handle, UINT width, UINT height)
				:cube_demo(handle,width,height){ }

			void update(float dt) override;
			void render() override;
		protected:


		};
	} // dx11 namespace 
} // engine namespace