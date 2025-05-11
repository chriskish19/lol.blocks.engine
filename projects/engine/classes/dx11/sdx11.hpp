/***********************************************
* File: sdx11.hpp (setup direct x 11)
*
*
*
*
*
************************************************/

#pragma once


#include LOGGER_NAMES_INCLUDE
#include LOGGER_ALL_LOGS_INCLUDE_PATH

namespace engine {
	namespace dx11 {

		struct device_description {
			~device_description();
			device_description() = default;

			IDXGIAdapter* pAdapter;
			D3D_DRIVER_TYPE				DriverType;
			HMODULE						Software;
			UINT						Flags;
			const D3D_FEATURE_LEVEL* pFeatureLevels;
			UINT						FeatureLevels;
			UINT						SDKVersion;
			const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc;
			IDXGISwapChain* pSwapChain;
			ID3D11Device* pDevice;
			D3D_FEATURE_LEVEL* pFeatureLevel;
			ID3D11DeviceContext* pImmediateContext;
		};

		// create device and swapchain
		HRESULT create_device(device_description* dd);

		// cbb : create back buffer
		ID3D11Texture2D* cbb(IDXGISwapChain* pSwapChain);

		// crtv : create render target view
		ID3D11RenderTargetView* crtv(ID3D11Device* pDevice, ID3D11Texture2D* pBackBuffer);

		// cdsb : create depth stencil buffer
		// p_dsd : depth stencil description pointer
		ID3D11Texture2D* cdsb(const D3D11_TEXTURE2D_DESC* p_dsd, ID3D11Device* p_device);

		// cdsv : create depth stencil view
		// p_dsvd : depth stencil view description pointer
		// p_dsb : depth stencil buffer pointer
		ID3D11DepthStencilView* cdsv(const D3D11_DEPTH_STENCIL_VIEW_DESC* p_dsvd, ID3D11Texture2D* p_dsb, ID3D11Device* p_device);
	}
}