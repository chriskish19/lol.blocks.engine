#include NAMES_INCLUDE
#include DX11SETUP_INCLUDE_PATH




HRESULT dx11::create_device(device_description* dd) {

	/*
	
	HRESULT D3D11CreateDeviceAndSwapChain(
		  [in, optional]  IDXGIAdapter               *pAdapter,
						  D3D_DRIVER_TYPE            DriverType,
						  HMODULE                    Software,
						  UINT                       Flags,
		  [in, optional]  const D3D_FEATURE_LEVEL    *pFeatureLevels,
						  UINT                       FeatureLevels,
						  UINT                       SDKVersion,
		  [in, optional]  const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
		  [out, optional] IDXGISwapChain             **ppSwapChain,
		  [out, optional] ID3D11Device               **ppDevice,
		  [out, optional] D3D_FEATURE_LEVEL          *pFeatureLevel,
		  [out, optional] ID3D11DeviceContext        **ppImmediateContext
		);
	
	*/
	IDXGISwapChain* p_sc = nullptr;
	ID3D11Device* p_d = nullptr;
	ID3D11DeviceContext* p_dc = nullptr;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		dd->pAdapter,
		dd->DriverType,
		dd->Software,
		dd->Flags,
		dd->pFeatureLevels,
		dd->FeatureLevels,
		dd->SDKVersion,
		dd->pSwapChainDesc,
		&p_sc,
		&p_d,
		dd->pFeatureLevel,
		&p_dc
	);

	dd->pSwapChain = p_sc;
	dd->pDevice = p_d;
	dd->pImmediateContext = p_dc;

	st_vs_out(hr);

	return hr;
}

dx11::device_description::~device_description()
{
	if (pAdapter != nullptr) {
		pAdapter->Release();
	}

	if (pFeatureLevels != nullptr) {
		delete pFeatureLevels;
		pFeatureLevels = nullptr;
	}

	if (pSwapChainDesc != nullptr) {
		delete pSwapChainDesc;
		pSwapChainDesc = nullptr;
	}

	if (pSwapChain != nullptr) {
		pSwapChain->Release();
	}

	if (pDevice != nullptr) {
		pDevice->Release();
	}
	
	if (pFeatureLevel != nullptr) {
		delete pFeatureLevel;
		pFeatureLevel = nullptr;
	}
	
	if (pImmediateContext != nullptr) {
		pImmediateContext->Release();
	}
}

ID3D11Texture2D* dx11::cbb(IDXGISwapChain* pSwapChain) {
	ID3D11Texture2D* p_back_buffer = nullptr;
	HRESULT hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_back_buffer);
	st_vs_out(hr);
	return p_back_buffer;
}

ID3D11RenderTargetView* dx11::crtv(ID3D11Device* pDevice, ID3D11Texture2D* pBackBuffer) {
	// render target view
	ID3D11RenderTargetView* p_rtv = nullptr;
	HRESULT hr = pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &p_rtv);
	st_vs_out(hr);
	return p_rtv;
}

ID3D11Texture2D* dx11::cdsb(const D3D11_TEXTURE2D_DESC* p_dsd, ID3D11Device* p_device) {
	// depth stencil buffer
	ID3D11Texture2D* p_dsb = nullptr;
	HRESULT hr = p_device->CreateTexture2D(p_dsd, nullptr, &p_dsb);
	st_vs_out(hr);
	return p_dsb;
}

ID3D11DepthStencilView* dx11::cdsv(const D3D11_DEPTH_STENCIL_VIEW_DESC* p_dsvd, ID3D11Texture2D* p_dsb, ID3D11Device* p_device) {
	// depth stencil view
	ID3D11DepthStencilView* p_dsv = nullptr;
	HRESULT hr = p_device->CreateDepthStencilView(p_dsb, p_dsvd, &p_dsv);
	st_vs_out(hr);
	return p_dsv;
}
