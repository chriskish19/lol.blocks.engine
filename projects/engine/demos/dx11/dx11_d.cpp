#include "dx11_d.hpp"
/***************************************
*  File: dx11_d.cpp (direct x 11 demos)
*
*  Purpose: dx11_d.hpp definitions
*
*  Project: engine
* *************************************/

#include ENGINE_NAMES_INCLUDE
#include ENGINE_DX11_DEMO_INCLUDE_PATH

engine::dx11::triangle_demo::triangle_demo(HWND handle,UINT width, UINT height)
{
	
	// driver types
	std::vector<D3D_DRIVER_TYPE> local_dt_v =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};
	
	
	// feature levels
	std::vector<D3D_FEATURE_LEVEL>* fl = new std::vector<D3D_FEATURE_LEVEL>
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// set the pointer
	m_p_dd->pFeatureLevels = fl->data();

	// set the number of feature levels
	m_p_dd->FeatureLevels = fl->size();


	// swap chain description
	DXGI_SWAP_CHAIN_DESC local_scd = {};
	local_scd.BufferCount = 1;
	local_scd.BufferDesc.Width = width;
	local_scd.BufferDesc.Height = height;
	local_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	local_scd.BufferDesc.RefreshRate.Numerator = 60;
	local_scd.BufferDesc.RefreshRate.Denominator = 1;
	local_scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	local_scd.OutputWindow = handle;
	local_scd.Windowed = true;
	local_scd.SampleDesc.Count = 1;
	local_scd.SampleDesc.Quality = 0;
	
	// creation flags
	unsigned int cf = 0;
#ifdef DX11_DEBUG
	cf |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	m_p_dd->Flags = cf;
	m_p_dd->pSwapChainDesc = new DXGI_SWAP_CHAIN_DESC(local_scd);
	m_p_dd->SDKVersion = D3D11_SDK_VERSION;

	for (auto type : local_dt_v) {
		m_p_dd->DriverType = type;
		HRESULT code = create_device(m_p_dd);
		if (SUCCEEDED(code)) {
			break;
		}
	}


	// create back buffer
	ID3D11Texture2D* p_bb = nullptr;
	p_bb = cbb(m_p_dd->pSwapChain);
	

	// create rtv
	ID3D11RenderTargetView* p_rtv = nullptr;
	p_rtv = crtv(m_p_dd->pDevice, p_bb);
	
	m_p_rtv = p_rtv;

	if (p_bb != nullptr) {
		p_bb->Release();
	}


	m_p_dd->pImmediateContext->OMSetRenderTargets(1, &p_rtv, 0);

	// view port description
	D3D11_VIEWPORT local_vp = {};
	local_vp.Width = static_cast<float>(width);
	local_vp.Height = static_cast<float>(height);
	local_vp.MinDepth = 0.0f;
	local_vp.MaxDepth = 1.0f;
	local_vp.TopLeftX = 0.0f;
	local_vp.TopLeftY = 0.0f;


	m_p_dd->pImmediateContext->RSSetViewports(1, &local_vp);

}

engine::dx11::triangle_demo::~triangle_demo()
{
	if (m_p_dd != nullptr) {
		delete m_p_dd;
		m_p_dd = nullptr;
	}

	if (m_p_rtv != nullptr) {
		m_p_rtv->Release();
	}

	if (m_il != nullptr) {
		m_il->Release();
	}

	if (m_sc_ps != nullptr) {
		m_sc_ps->Release();
	}

	if (m_sc_vs != nullptr) {
		m_sc_vs->Release();
	}

	if (m_vsb != nullptr) {
		m_vsb->Release();
	}

	if (m_vb != nullptr) {
		m_vb->Release();
	}
}

engine::codes engine::dx11::triangle_demo::load_content()
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef DX11_DEBUG
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif


	/*
	
	HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);
	
	*/


	{
		ID3DBlob* eb = nullptr; // error buffer
		HRESULT hr;
		hr = D3DCompileFromFile(
			ENGINE_TDDX11VS_FILE_PATH, 
			nullptr, 
			nullptr, 
			"VS_Main", 
			"vs_4_0",
			shaderFlags,
			0, 
			&m_vsb, 
			&eb
		);


		output_hr(hr);
		if (FAILED(hr)) {
			codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return codes::dx_error;
		}
	}
	
	// create vertex shader
	{
		/*
		
					HRESULT CreateVertexShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11VertexShader **ppVertexShader
			);
		
		*/
		
		
		HRESULT hr = m_p_dd->pDevice->CreateVertexShader(
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			nullptr,
			&m_sc_vs
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// vertex layout
	D3D11_INPUT_ELEMENT_DESC vl[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
						D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	
	// number of elements in vertex layout
	UINT no_vl_e = std::size(vl);

	/*
	
			HRESULT CreateInputLayout(
		  [in]            const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
		  [in]            UINT                           NumElements,
		  [in]            const void                     *pShaderBytecodeWithInputSignature,
		  [in]            SIZE_T                         BytecodeLength,
		  [out, optional] ID3D11InputLayout              **ppInputLayout
		);
	
	*/

	{
		HRESULT hr = m_p_dd->pDevice->CreateInputLayout(
			vl,
			no_vl_e,
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			&m_il
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// compile pixel shader
	{
		/*
		
		HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);
	
		
		*/
		
		
		// error buffer
		ID3DBlob* eb = nullptr;

		HRESULT hr = D3DCompileFromFile(
			ENGINE_TDDX11PS_FILE_PATH,
			nullptr,
			nullptr,
			"PS_Main",
			"ps_4_0",
			shaderFlags,
			0,
			&m_psb,
			&eb
		);

		output_hr(hr);
		if (FAILED(hr)) {
			codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return codes::dx_error;
		}
	

	}


	// create pixel shader
	{
		/*
		
					HRESULT CreatePixelShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11PixelShader  **ppPixelShader
			);
		
		*/
		
		
		HRESULT hr = m_p_dd->pDevice->CreatePixelShader(
			m_psb->GetBufferPointer(),
			m_psb->GetBufferSize(),
			nullptr,
			&m_sc_ps
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}

	}



	VertexPos vertices[]
	{
		DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)
	};

	D3D11_BUFFER_DESC vertexDesc = {};
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos) * 3;

	D3D11_SUBRESOURCE_DATA resourceData = {};
	resourceData.pSysMem = vertices;

	// create vertex buffer
	{
		HRESULT hr = m_p_dd->pDevice->CreateBuffer(
			&vertexDesc,
			&resourceData,
			&m_vb
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}

	}

	return codes::success;
}

void engine::dx11::triangle_demo::unload_content()
{

}

void engine::dx11::triangle_demo::update(float dt)
{

}

void engine::dx11::triangle_demo::render()
{
	if (m_p_dd->pImmediateContext == 0)
		return;
	
	float clear_color[4] = { 0.0f, 0.0f, 0.25f, 1.0f };

	m_p_dd->pImmediateContext->ClearRenderTargetView(m_p_rtv, clear_color);

	unsigned int stride = sizeof(VertexPos);
	unsigned int offset = 0;


	m_p_dd->pImmediateContext->IASetInputLayout(m_il);
	m_p_dd->pImmediateContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	m_p_dd->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_p_dd->pImmediateContext->VSSetShader(m_sc_vs, 0, 0);
	m_p_dd->pImmediateContext->PSSetShader(m_sc_ps, 0, 0);
	m_p_dd->pImmediateContext->Draw(3, 0);



	m_p_dd->pSwapChain->Present(0, 0);
}

engine::dx11::texture_demo::texture_demo(HWND handle, UINT width, UINT height)
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	output_hr(hr);
	
	
	// driver types
	std::vector<D3D_DRIVER_TYPE> local_dt_v =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};


	// feature levels
	std::vector<D3D_FEATURE_LEVEL>* fl = new std::vector<D3D_FEATURE_LEVEL>
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// set the pointer
	m_p_dd->pFeatureLevels = fl->data();

	// set the number of feature levels
	m_p_dd->FeatureLevels = fl->size();


	// swap chain description
	DXGI_SWAP_CHAIN_DESC local_scd = {};
	local_scd.BufferCount = 1;
	local_scd.BufferDesc.Width = width;
	local_scd.BufferDesc.Height = height;
	local_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	local_scd.BufferDesc.RefreshRate.Numerator = 60;
	local_scd.BufferDesc.RefreshRate.Denominator = 1;
	local_scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	local_scd.OutputWindow = handle;
	local_scd.Windowed = true;
	local_scd.SampleDesc.Count = 1;
	local_scd.SampleDesc.Quality = 0;

	// creation flags
	unsigned int cf = 0;
#ifdef DX11_DEBUG
	cf |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	m_p_dd->Flags = cf;
	m_p_dd->pSwapChainDesc = new DXGI_SWAP_CHAIN_DESC(local_scd);
	m_p_dd->SDKVersion = D3D11_SDK_VERSION;

	for (auto type : local_dt_v) {
		m_p_dd->DriverType = type;
		HRESULT code = create_device(m_p_dd);
		if (SUCCEEDED(code)) {
			break;
		}
	}


	// create back buffer
	ID3D11Texture2D* p_bb = nullptr;
	p_bb = cbb(m_p_dd->pSwapChain);


	// create rtv
	ID3D11RenderTargetView* p_rtv = nullptr;
	p_rtv = crtv(m_p_dd->pDevice, p_bb);

	m_p_rtv = p_rtv;

	if (p_bb != nullptr) {
		p_bb->Release();
	}


	m_p_dd->pImmediateContext->OMSetRenderTargets(1, &p_rtv, 0);

	// view port description
	D3D11_VIEWPORT local_vp = {};
	local_vp.Width = static_cast<float>(width);
	local_vp.Height = static_cast<float>(height);
	local_vp.MinDepth = 0.0f;
	local_vp.MaxDepth = 1.0f;
	local_vp.TopLeftX = 0.0f;
	local_vp.TopLeftY = 0.0f;


	m_p_dd->pImmediateContext->RSSetViewports(1, &local_vp);
}

engine::dx11::texture_demo::~texture_demo()
{
	if (m_p_dd != nullptr) {
		delete m_p_dd;
		m_p_dd = nullptr;
	}

	if (m_p_rtv != nullptr) {
		m_p_rtv->Release();
	}

	if (m_il != nullptr) {
		m_il->Release();
	}

	if (m_cm_ps != nullptr) {
		m_cm_ps->Release();
	}

	if (m_cm_vs != nullptr) {
		m_cm_vs->Release();
	}

	if (m_vsb != nullptr) {
		m_vsb->Release();
	}

	if (m_vb != nullptr) {
		m_vb->Release();
	}

	if (m_tx != nullptr) {
		m_tx->Release();
	}

	if (m_cms != nullptr) {
		m_cms->Release();
	}
}

engine::codes engine::dx11::texture_demo::load_content()
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef DX11_DEBUG
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif


	/*

	HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);

	*/

	// compiling vertex shader
	{
		ID3DBlob* eb = nullptr; // error buffer
		HRESULT hr;
		hr = D3DCompileFromFile(
			ENGINE_TXDDX11VS_FILE_PATH,
			nullptr,
			nullptr,
			"VS_Main",
			"vs_4_0",
			shaderFlags,
			0,
			&m_vsb,
			&eb
		);


		output_hr(hr);
		if (FAILED(hr)) {
			codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return codes::dx_error;
		}
	}

	// create vertex shader
	{
		/*

					HRESULT CreateVertexShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11VertexShader **ppVertexShader
			);

		*/


		HRESULT hr = m_p_dd->pDevice->CreateVertexShader(
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			nullptr,
			&m_cm_vs
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// solid color layout
	D3D11_INPUT_ELEMENT_DESC scl[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
						0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
					0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// number of elements in vertex layout
	UINT no_vl_e = std::size(scl);

	/*

			HRESULT CreateInputLayout(
		  [in]            const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
		  [in]            UINT                           NumElements,
		  [in]            const void                     *pShaderBytecodeWithInputSignature,
		  [in]            SIZE_T                         BytecodeLength,
		  [out, optional] ID3D11InputLayout              **ppInputLayout
		);

	*/

	{
		HRESULT hr = m_p_dd->pDevice->CreateInputLayout(
			scl,
			no_vl_e,
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			&m_il
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// compile pixel shader
	{
		/*

		HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);


		*/


		// error buffer
		ID3DBlob* eb = nullptr;

		HRESULT hr = D3DCompileFromFile(
			ENGINE_TXDDX11PS_FILE_PATH,
			nullptr,
			nullptr,
			"PS_Main",
			"ps_4_0",
			shaderFlags,
			0,
			&m_psb,
			&eb
		);

		output_hr(hr);
		if (FAILED(hr)) {
			codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return codes::dx_error;
		}


	}


	// create pixel shader
	{
		/*

					HRESULT CreatePixelShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11PixelShader  **ppPixelShader
			);

		*/


		HRESULT hr = m_p_dd->pDevice->CreatePixelShader(
			m_psb->GetBufferPointer(),
			m_psb->GetBufferSize(),
			nullptr,
			&m_cm_ps
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}

	}



	VertexPos vertices[] =
	{
		{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),		DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f),		DirectX::XMFLOAT2(1.0f, 0.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f),	DirectX::XMFLOAT2(0.0f, 0.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f),	DirectX::XMFLOAT2(0.0f, 0.0f) },
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),		DirectX::XMFLOAT2(0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),		DirectX::XMFLOAT2(1.0f, 1.0f) },
	};

	D3D11_BUFFER_DESC vertexDesc = {};
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos) * 6;

	D3D11_SUBRESOURCE_DATA resourceData = {};
	resourceData.pSysMem = vertices;

	// create vertex buffer
	{
		HRESULT hr = m_p_dd->pDevice->CreateBuffer(
			&vertexDesc,
			&resourceData,
			&m_vb
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}

	}


	{
		HRESULT hr = DirectX::CreateWICTextureFromFile(
			m_p_dd->pDevice,
			m_p_dd->pImmediateContext,
			ENGINE_TX_GRAPH,
			nullptr,
			&m_tx
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// color map description
	D3D11_SAMPLER_DESC cmpd = {};
	cmpd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	cmpd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	cmpd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	cmpd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	cmpd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	cmpd.MaxLOD = D3D11_FLOAT32_MAX;

	{
		HRESULT hr = m_p_dd->pDevice->CreateSamplerState(&cmpd, &m_cms);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	return codes::success;
}

void engine::dx11::texture_demo::unload_content()
{
}

void engine::dx11::texture_demo::update(float dt)
{
}

void engine::dx11::texture_demo::render()
{
	if (m_p_dd->pImmediateContext == 0)
		return;

	float clearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	m_p_dd->pImmediateContext->ClearRenderTargetView(m_p_rtv, clearColor);
	unsigned int stride = sizeof(VertexPos);
	unsigned int offset = 0;
	m_p_dd->pImmediateContext->IASetInputLayout(m_il);
	m_p_dd->pImmediateContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);

	m_p_dd->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_p_dd->pImmediateContext->VSSetShader(m_cm_vs, 0, 0);
	m_p_dd->pImmediateContext->PSSetShader(m_cm_ps, 0, 0);
	m_p_dd->pImmediateContext->PSSetShaderResources(0, 1, &m_tx);
	m_p_dd->pImmediateContext->PSSetSamplers(0, 1, &m_cms);
	m_p_dd->pImmediateContext->Draw(6, 0);
	m_p_dd->pSwapChain->Present(0, 0);
}

engine::dx11::simple_tx_demo::simple_tx_demo(HWND handle, UINT width, UINT height)
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	output_hr(hr);


	// driver types
	std::vector<D3D_DRIVER_TYPE> local_dt_v =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};


	// feature levels
	std::vector<D3D_FEATURE_LEVEL>* fl = new std::vector<D3D_FEATURE_LEVEL>
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// set the pointer
	m_p_dd->pFeatureLevels = fl->data();

	// set the number of feature levels
	m_p_dd->FeatureLevels = fl->size();


	// swap chain description
	DXGI_SWAP_CHAIN_DESC local_scd = {};
	local_scd.BufferCount = 1;
	local_scd.BufferDesc.Width = width;
	local_scd.BufferDesc.Height = height;
	local_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	local_scd.BufferDesc.RefreshRate.Numerator = 60;
	local_scd.BufferDesc.RefreshRate.Denominator = 1;
	local_scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	local_scd.OutputWindow = handle;
	local_scd.Windowed = true;
	local_scd.SampleDesc.Count = 1;
	local_scd.SampleDesc.Quality = 0;

	// creation flags
	unsigned int cf = 0;
#ifdef DX11_DEBUG
	cf |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	m_p_dd->Flags = cf;
	m_p_dd->pSwapChainDesc = new DXGI_SWAP_CHAIN_DESC(local_scd);
	m_p_dd->SDKVersion = D3D11_SDK_VERSION;

	for (auto type : local_dt_v) {
		m_p_dd->DriverType = type;
		HRESULT code = create_device(m_p_dd);
		if (SUCCEEDED(code)) {
			break;
		}
	}


	// create back buffer
	ID3D11Texture2D* p_bb = nullptr;
	p_bb = cbb(m_p_dd->pSwapChain);


	// create rtv
	ID3D11RenderTargetView* p_rtv = nullptr;
	p_rtv = crtv(m_p_dd->pDevice, p_bb);

	m_p_rtv = p_rtv;

	if (p_bb != nullptr) {
		p_bb->Release();
	}


	m_p_dd->pImmediateContext->OMSetRenderTargets(1, &p_rtv, 0);

	// view port description
	D3D11_VIEWPORT local_vp = {};
	local_vp.Width = static_cast<float>(width);
	local_vp.Height = static_cast<float>(height);
	local_vp.MinDepth = 0.0f;
	local_vp.MaxDepth = 1.0f;
	local_vp.TopLeftX = 0.0f;
	local_vp.TopLeftY = 0.0f;


	m_p_dd->pImmediateContext->RSSetViewports(1, &local_vp);
}

engine::dx11::simple_tx_demo::~simple_tx_demo()
{
	if (m_p_dd != nullptr) {
		delete m_p_dd;
		m_p_dd = nullptr;
	}

	if (m_p_rtv != nullptr) {
		m_p_rtv->Release();
	}

	if (m_sb != nullptr) {
		delete m_sb;
		m_sb = nullptr;
	}

	if (m_tx != nullptr) {
		m_tx->Release();
	}
}

engine::codes engine::dx11::simple_tx_demo::load_content()
{
	// make a sprite batch
	m_sb = new DirectX::SpriteBatch(m_p_dd->pImmediateContext);

	// load texture
	{
		HRESULT hr = DirectX::CreateWICTextureFromFile(
			m_p_dd->pDevice,
			m_p_dd->pImmediateContext,
			ENGINE_TX_GRAPH,
			nullptr,
			&m_tx
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	return codes::success;
}

void engine::dx11::simple_tx_demo::unload_content()
{
}

void engine::dx11::simple_tx_demo::update(float dt)
{
}

void engine::dx11::simple_tx_demo::render()
{
	m_p_dd->pImmediateContext->ClearRenderTargetView(m_p_rtv, DirectX::Colors::Black);

	m_sb->Begin();
	m_sb->Draw(m_tx, DirectX::XMFLOAT2(0, 0)); // top-left corner
	m_sb->End();

	m_p_dd->pSwapChain->Present(0, 0);
}

engine::dx11::ss_demo::ss_demo(HWND handle, UINT width, UINT height)
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	output_hr(hr);


	// driver types
	std::vector<D3D_DRIVER_TYPE> local_dt_v =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};


	// feature levels
	std::vector<D3D_FEATURE_LEVEL>* fl = new std::vector<D3D_FEATURE_LEVEL>
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// set the pointer
	m_p_dd->pFeatureLevels = fl->data();

	// set the number of feature levels
	m_p_dd->FeatureLevels = fl->size();


	// swap chain description
	DXGI_SWAP_CHAIN_DESC local_scd = {};
	local_scd.BufferCount = 1;
	local_scd.BufferDesc.Width = width;
	local_scd.BufferDesc.Height = height;
	local_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	local_scd.BufferDesc.RefreshRate.Numerator = 60;
	local_scd.BufferDesc.RefreshRate.Denominator = 1;
	local_scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	local_scd.OutputWindow = handle;
	local_scd.Windowed = true;
	local_scd.SampleDesc.Count = 1;
	local_scd.SampleDesc.Quality = 0;

	// creation flags
	unsigned int cf = 0;
#ifdef DX11_DEBUG
	cf |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	m_p_dd->Flags = cf;
	m_p_dd->pSwapChainDesc = new DXGI_SWAP_CHAIN_DESC(local_scd);
	m_p_dd->SDKVersion = D3D11_SDK_VERSION;

	for (auto type : local_dt_v) {
		m_p_dd->DriverType = type;
		HRESULT code = create_device(m_p_dd);
		if (SUCCEEDED(code)) {
			break;
		}
	}


	// create back buffer
	ID3D11Texture2D* p_bb = nullptr;
	p_bb = cbb(m_p_dd->pSwapChain);


	// create rtv
	ID3D11RenderTargetView* p_rtv = nullptr;
	p_rtv = crtv(m_p_dd->pDevice, p_bb);

	m_p_rtv = p_rtv;

	if (p_bb != nullptr) {
		p_bb->Release();
	}


	m_p_dd->pImmediateContext->OMSetRenderTargets(1, &p_rtv, 0);

	// view port description
	D3D11_VIEWPORT local_vp = {};
	local_vp.Width = static_cast<float>(width);
	local_vp.Height = static_cast<float>(height);
	local_vp.MinDepth = 0.0f;
	local_vp.MaxDepth = 1.0f;
	local_vp.TopLeftX = 0.0f;
	local_vp.TopLeftY = 0.0f;


	m_p_dd->pImmediateContext->RSSetViewports(1, &local_vp);
}

engine::dx11::ss_demo::~ss_demo()
{
	if (m_p_dd != nullptr) {
		delete m_p_dd;
		m_p_dd = nullptr;
	}

	if (m_p_rtv != nullptr) {
		m_p_rtv->Release();
	}

	if (m_sb != nullptr) {
		delete m_sb;
		m_sb = nullptr;
	}

	if (m_tx != nullptr) {
		m_tx->Release();
	}

	if (m_kbd != nullptr) {
		delete m_kbd;
		m_kbd = nullptr;
	}

	if (m_cs != nullptr) {
		delete m_cs;
		m_cs = nullptr;
	}
}

engine::codes engine::dx11::ss_demo::load_content()
{
	// init keyboard
	m_kbd = new DirectX::Keyboard;

	// init states
	m_cs = new DirectX::CommonStates(m_p_dd->pDevice);
	
	// make a sprite batch
	m_sb = new DirectX::SpriteBatch(m_p_dd->pImmediateContext);

	// load texture
	{
		HRESULT hr = DirectX::CreateWICTextureFromFile(
			m_p_dd->pDevice,
			m_p_dd->pImmediateContext,
			ENGINE_TX_STICK,
			nullptr,
			&m_tx
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	return codes::success;
}

void engine::dx11::ss_demo::unload_content()
{

}

void engine::dx11::ss_demo::update(float dt)
{
	timeSinceLastFrame += dt;

	if (timeSinceLastFrame >= frameTime)
	{
		currentFrame = (currentFrame + 1) % totalFrames;
		timeSinceLastFrame = 0.0f;
	}

	auto kb = m_kbd->GetState();

	if (kb.Left)  characterPos.x -= moveSpeed * dt;
	if (kb.Right) characterPos.x += moveSpeed * dt;
	if (kb.Up)    characterPos.y -= moveSpeed * dt;
	if (kb.Down)  characterPos.y += moveSpeed * dt;
}

void engine::dx11::ss_demo::render()
{
	m_p_dd->pImmediateContext->ClearRenderTargetView(m_p_rtv, DirectX::Colors::White);
	m_p_dd->pImmediateContext->OMSetBlendState(m_cs->AlphaBlend(), nullptr, 0xFFFFFFFF);

	// Compute source RECT from frame index
	int frameX = (currentFrame % 2) * frameWidth;
	int frameY = (currentFrame / 2) * frameHeight;

	RECT sourceRect = {
		frameX,
		frameY,
		frameX + frameWidth,
		frameY + frameHeight
	};

	m_sb->Begin();
	m_sb->Draw(m_tx, characterPos, &sourceRect);
	m_sb->End();

	m_p_dd->pSwapChain->Present(0, 0);
}

engine::dx11::camera_demo::camera_demo(HWND handle, UINT width, UINT height)
{
	// init direct xtk
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	output_hr(hr);
	
	
	// driver types
	std::vector<D3D_DRIVER_TYPE> local_dt_v =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};


	// feature levels
	std::vector<D3D_FEATURE_LEVEL>* fl = new std::vector<D3D_FEATURE_LEVEL>
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// set the pointer
	m_p_dd->pFeatureLevels = fl->data();

	// set the number of feature levels
	m_p_dd->FeatureLevels = fl->size();


	// swap chain description
	DXGI_SWAP_CHAIN_DESC local_scd = {};
	local_scd.BufferCount = 1;
	local_scd.BufferDesc.Width = width;
	local_scd.BufferDesc.Height = height;
	local_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	local_scd.BufferDesc.RefreshRate.Numerator = 60;
	local_scd.BufferDesc.RefreshRate.Denominator = 1;
	local_scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	local_scd.OutputWindow = handle;
	local_scd.Windowed = true;
	local_scd.SampleDesc.Count = 1;
	local_scd.SampleDesc.Quality = 0;

	// creation flags
	unsigned int cf = 0;
#ifdef DX11_DEBUG
	cf |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	m_p_dd->Flags = cf;
	m_p_dd->pSwapChainDesc = new DXGI_SWAP_CHAIN_DESC(local_scd);
	m_p_dd->SDKVersion = D3D11_SDK_VERSION;

	for (auto type : local_dt_v) {
		m_p_dd->DriverType = type;
		HRESULT code = create_device(m_p_dd);
		if (SUCCEEDED(code)) {
			break;
		}
	}


	// create back buffer
	ID3D11Texture2D* p_bb = nullptr;
	p_bb = cbb(m_p_dd->pSwapChain);


	// create rtv
	ID3D11RenderTargetView* p_rtv = nullptr;
	p_rtv = crtv(m_p_dd->pDevice, p_bb);

	m_p_rtv = p_rtv;

	if (p_bb != nullptr) {
		p_bb->Release();
	}


	m_p_dd->pImmediateContext->OMSetRenderTargets(1, &p_rtv, 0);

	// view port description
	D3D11_VIEWPORT local_vp = {};
	local_vp.Width = static_cast<float>(width);
	local_vp.Height = static_cast<float>(height);
	local_vp.MinDepth = 0.0f;
	local_vp.MaxDepth = 1.0f;
	local_vp.TopLeftX = 0.0f;
	local_vp.TopLeftY = 0.0f;


	m_p_dd->pImmediateContext->RSSetViewports(1, &local_vp);


	// init camera
	float fov = 70.0f;                  // Field of view in degrees
	float aspectRatio = static_cast<float>(width / height); 
	float nearZ = 0.1f;
	float farZ = 1000.0f;
	m_cam = Camera(fov, aspectRatio, nearZ, farZ);

}

engine::dx11::camera_demo::~camera_demo()
{
	if (m_p_dd != nullptr) {
		delete m_p_dd;
		m_p_dd = nullptr;
	}

	if (m_p_rtv != nullptr) {
		m_p_rtv->Release();
	}

	if (m_il != nullptr) {
		m_il->Release();
	}

	if (m_sc_ps != nullptr) {
		m_sc_ps->Release();
	}

	if (m_sc_vs != nullptr) {
		m_sc_vs->Release();
	}

	if (m_vsb != nullptr) {
		m_vsb->Release();
	}

	if (m_vb != nullptr) {
		m_vb->Release();
	}

	if (m_kbd != nullptr) {
		delete m_kbd;
		m_kbd = nullptr;
	}

	if (m_cameraCB != nullptr) {
		m_cameraCB->Release();
	}
}

engine::codes engine::dx11::camera_demo::load_content()
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef DX11_DEBUG
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif


	/*

	HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);

	*/


	{
		ID3DBlob* eb = nullptr; // error buffer
		HRESULT hr;
		hr = D3DCompileFromFile(
			ENGINE_CDDX11VS_FILE_PATH,
			nullptr,
			nullptr,
			"VS_Main",
			"vs_4_0",
			shaderFlags,
			0,
			&m_vsb,
			&eb
		);


		output_hr(hr);
		if (FAILED(hr)) {
			codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return codes::dx_error;
		}
	}

	// create vertex shader
	{
		/*

					HRESULT CreateVertexShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11VertexShader **ppVertexShader
			);

		*/


		HRESULT hr = m_p_dd->pDevice->CreateVertexShader(
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			nullptr,
			&m_sc_vs
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// vertex layout
	D3D11_INPUT_ELEMENT_DESC vl[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
						D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// number of elements in vertex layout
	UINT no_vl_e = std::size(vl);

	/*

			HRESULT CreateInputLayout(
		  [in]            const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
		  [in]            UINT                           NumElements,
		  [in]            const void                     *pShaderBytecodeWithInputSignature,
		  [in]            SIZE_T                         BytecodeLength,
		  [out, optional] ID3D11InputLayout              **ppInputLayout
		);

	*/

	{
		HRESULT hr = m_p_dd->pDevice->CreateInputLayout(
			vl,
			no_vl_e,
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			&m_il
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// compile pixel shader
	{
		/*

		HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);


		*/


		// error buffer
		ID3DBlob* eb = nullptr;

		HRESULT hr = D3DCompileFromFile(
			ENGINE_CDDX11PS_FILE_PATH,
			nullptr,
			nullptr,
			"PS_Main",
			"ps_4_0",
			shaderFlags,
			0,
			&m_psb,
			&eb
		);

		output_hr(hr);
		if (FAILED(hr)) {
			codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return codes::dx_error;
		}


	}


	// create pixel shader
	{
		/*

					HRESULT CreatePixelShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11PixelShader  **ppPixelShader
			);

		*/


		HRESULT hr = m_p_dd->pDevice->CreatePixelShader(
			m_psb->GetBufferPointer(),
			m_psb->GetBufferSize(),
			nullptr,
			&m_sc_ps
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}

	}



	VertexPos vertices[]
	{
		DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)
	};

	D3D11_BUFFER_DESC vertexDesc = {};
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos) * 3;

	D3D11_SUBRESOURCE_DATA resourceData = {};
	resourceData.pSysMem = vertices;

	// create vertex buffer
	{
		HRESULT hr = m_p_dd->pDevice->CreateBuffer(
			&vertexDesc,
			&resourceData,
			&m_vb
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}

	}



	// create the camera buffer gpu side
	D3D11_BUFFER_DESC cbd = {};
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = sizeof(CameraBuffer);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = 0;
	cbd.MiscFlags = 0;

	{
		HRESULT hr = m_p_dd->pDevice->CreateBuffer(&cbd, nullptr, &m_cameraCB);
		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// init keyboard
	m_kbd = new DirectX::Keyboard;


	return codes::success;
}

void engine::dx11::camera_demo::unload_content()
{
}

void engine::dx11::camera_demo::update(float dt)
{

	auto kb = m_kbd->GetState();

	// Move
	if (kb.W)			m_cam.MoveForward(dt * moveSpeed);
	if (kb.S)			m_cam.MoveForward(-dt * moveSpeed);
	if (kb.A)			m_cam.MoveRight(-dt * moveSpeed);
	if (kb.D)			m_cam.MoveRight(dt * moveSpeed);
	if (kb.Space)		m_cam.MoveUp(dt * moveSpeed);
	if (kb.LeftShift)	m_cam.MoveUp(-dt * moveSpeed);

	m_cam.UpdateView();
}

void engine::dx11::camera_demo::render()
{
	if (m_p_dd->pImmediateContext == 0)
		return;

	float clear_color[4] = { 0.0f, 0.0f, 0.25f, 1.0f };

	m_p_dd->pImmediateContext->ClearRenderTargetView(m_p_rtv, clear_color);

	unsigned int stride = sizeof(VertexPos);
	unsigned int offset = 0;


	m_p_dd->pImmediateContext->IASetInputLayout(m_il);

	CameraBuffer cb = {};
	cb.view = DirectX::XMMatrixTranspose(m_cam.GetViewMatrix());
	cb.projection = DirectX::XMMatrixTranspose(m_cam.GetProjectionMatrix());
	m_p_dd->pImmediateContext->UpdateSubresource(m_cameraCB, 0, nullptr, &cb, 0, 0);

	m_p_dd->pImmediateContext->VSSetConstantBuffers(0, 1, &m_cameraCB);
	m_p_dd->pImmediateContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	m_p_dd->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_p_dd->pImmediateContext->VSSetShader(m_sc_vs, 0, 0);
	m_p_dd->pImmediateContext->PSSetShader(m_sc_ps, 0, 0);
	m_p_dd->pImmediateContext->Draw(3, 0);

	m_p_dd->pSwapChain->Present(0, 0);
}

engine::dx11::cube_demo::cube_demo(HWND handle, UINT width, UINT height)
	:m_handle(handle),m_width(width),m_height(height)
{
	// init direct xtk
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	output_hr(hr);

	// init mouse
	m_ms = new DirectX::Mouse;
	m_ms->SetWindow(handle);
	m_ms->SetMode(DirectX::Mouse::MODE_RELATIVE);


	// driver types
	std::vector<D3D_DRIVER_TYPE> local_dt_v =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};


	// feature levels
	std::vector<D3D_FEATURE_LEVEL>* fl = new std::vector<D3D_FEATURE_LEVEL>
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// set the pointer
	m_p_dd->pFeatureLevels = fl->data();

	// set the number of feature levels
	m_p_dd->FeatureLevels = fl->size();


	// swap chain description
	DXGI_SWAP_CHAIN_DESC local_scd = {};
	local_scd.BufferCount = 1;
	local_scd.BufferDesc.Width = width;
	local_scd.BufferDesc.Height = height;
	local_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	local_scd.BufferDesc.RefreshRate.Numerator = 60;
	local_scd.BufferDesc.RefreshRate.Denominator = 1;
	local_scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	local_scd.OutputWindow = handle;
	local_scd.Windowed = true;
	local_scd.SampleDesc.Count = 1;
	local_scd.SampleDesc.Quality = 0;

	// creation flags
	unsigned int cf = 0;
#ifdef DX11_DEBUG
	cf |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	m_p_dd->Flags = cf;
	m_p_dd->pSwapChainDesc = new DXGI_SWAP_CHAIN_DESC(local_scd);
	m_p_dd->SDKVersion = D3D11_SDK_VERSION;

	for (auto type : local_dt_v) {
		m_p_dd->DriverType = type;
		HRESULT code = create_device(m_p_dd);
		if (SUCCEEDED(code)) {
			break;
		}
	}


	// create back buffer
	ID3D11Texture2D* p_bb = nullptr;
	p_bb = cbb(m_p_dd->pSwapChain);


	// create rtv
	ID3D11RenderTargetView* p_rtv = nullptr;
	p_rtv = crtv(m_p_dd->pDevice, p_bb);

	m_p_rtv = p_rtv;

	if (p_bb != nullptr) {
		p_bb->Release();
	}


	m_p_dd->pImmediateContext->OMSetRenderTargets(1, &p_rtv, 0);

	// view port description
	D3D11_VIEWPORT local_vp = {};
	local_vp.Width = static_cast<float>(width);
	local_vp.Height = static_cast<float>(height);
	local_vp.MinDepth = 0.0f;
	local_vp.MaxDepth = 1.0f;
	local_vp.TopLeftX = 0.0f;
	local_vp.TopLeftY = 0.0f;


	m_p_dd->pImmediateContext->RSSetViewports(1, &local_vp);

	// init camera
	float fov = 70.0f;                  // Field of view in degrees
	float aspectRatio = static_cast<float>(width / height);
	float nearZ = 0.1f;
	float farZ = 1000.0f;
	m_cam = Camera(fov, aspectRatio, nearZ, farZ);


	D3D11_TEXTURE2D_DESC depthDesc = {};
	depthDesc.Width = width;       // same as swap chain
	depthDesc.Height = height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* depthStencilBuffer = cdsb(&depthDesc, m_p_dd->pDevice);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = depthDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	m_p_dsv = cdsv(&dsvDesc,depthStencilBuffer, m_p_dd->pDevice);
}

engine::dx11::cube_demo::~cube_demo()
{
	if (m_p_dd != nullptr) {
		delete m_p_dd;
		m_p_dd = nullptr;
	}

	if (m_p_rtv != nullptr) {
		m_p_rtv->Release();
	}

	if (m_il != nullptr) {
		m_il->Release();
	}

	if (m_sc_ps != nullptr) {
		m_sc_ps->Release();
	}

	if (m_sc_vs != nullptr) {
		m_sc_vs->Release();
	}

	if (m_vsb != nullptr) {
		m_vsb->Release();
	}

	if (m_vb != nullptr) {
		m_vb->Release();
	}

	if (m_kbd != nullptr) {
		delete m_kbd;
		m_kbd = nullptr;
	}

	if (m_ms != nullptr) {
		delete m_ms;
		m_ms = nullptr;
	}

	if (m_cameraCB != nullptr) {
		m_cameraCB->Release();
	}

	if (m_timeBuffer != nullptr) {
		m_timeBuffer->Release();
	}

	if (m_p_dsv != nullptr) {
		m_p_dsv->Release();
	}
}

engine::codes engine::dx11::cube_demo::load_content()
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef DX11_DEBUG
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif


	/*

	HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);

	*/


	{
		ID3DBlob* eb = nullptr; // error buffer
		HRESULT hr;
		hr = D3DCompileFromFile(
			ENGINE_CBDDX11VS_FILE_PATH,
			nullptr,
			nullptr,
			"VS_Main",
			"vs_4_0",
			shaderFlags,
			0,
			&m_vsb,
			&eb
		);


		output_hr(hr);
		if (FAILED(hr)) {
			codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return codes::dx_error;
		}
	}

	// create vertex shader
	{
		/*

					HRESULT CreateVertexShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11VertexShader **ppVertexShader
			);

		*/


		HRESULT hr = m_p_dd->pDevice->CreateVertexShader(
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			nullptr,
			&m_sc_vs
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// vertex layout
	D3D11_INPUT_ELEMENT_DESC vl[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
						D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// number of elements in vertex layout
	UINT no_vl_e = std::size(vl);

	/*

			HRESULT CreateInputLayout(
		  [in]            const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
		  [in]            UINT                           NumElements,
		  [in]            const void                     *pShaderBytecodeWithInputSignature,
		  [in]            SIZE_T                         BytecodeLength,
		  [out, optional] ID3D11InputLayout              **ppInputLayout
		);

	*/

	{
		HRESULT hr = m_p_dd->pDevice->CreateInputLayout(
			vl,
			no_vl_e,
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			&m_il
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// compile pixel shader
	{
		/*

		HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);


		*/


		// error buffer
		ID3DBlob* eb = nullptr;

		HRESULT hr = D3DCompileFromFile(
			ENGINE_CBDDX11PS_FILE_PATH,
			nullptr,
			nullptr,
			"PS_Main",
			"ps_4_0",
			shaderFlags,
			0,
			&m_psb,
			&eb
		);

		output_hr(hr);
		if (FAILED(hr)) {
			codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return codes::dx_error;
		}


	}


	// create pixel shader
	{
		/*

					HRESULT CreatePixelShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11PixelShader  **ppPixelShader
			);

		*/


		HRESULT hr = m_p_dd->pDevice->CreatePixelShader(
			m_psb->GetBufferPointer(),
			m_psb->GetBufferSize(),
			nullptr,
			&m_sc_ps
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}

	}

	// init the cube vertices
	size sz = { 1024,1024,1024 };
	for (std::size_t i = 0; i < 1000; ++i) {
		position p = { static_cast<float>(i),0.0f,static_cast<float>(i) };
		auto cube = create_cube(sz, p);
		auto cube_v = cube_to_vb(cube);
		for (const auto& v : cube_v) {
			m_cube_vertices.push_back(v);
		}
	}


	D3D11_BUFFER_DESC vertexDesc = {};
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = static_cast<UINT>(sizeof(DirectX::XMFLOAT3) * m_cube_vertices.size());
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA resourceData = {};
	resourceData.pSysMem = m_cube_vertices.data();

	// create vertex buffer
	{
		HRESULT hr = m_p_dd->pDevice->CreateBuffer(
			&vertexDesc,
			&resourceData,
			&m_vb
		);

		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}

	}

	// create the camera buffer gpu side
	D3D11_BUFFER_DESC cbd = {};
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = sizeof(CameraBuffer);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = 0;
	cbd.MiscFlags = 0;

	{
		HRESULT hr = m_p_dd->pDevice->CreateBuffer(&cbd, nullptr, &m_cameraCB);
		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}

	// create time buffer gpu side
	D3D11_BUFFER_DESC timeBufferDesc = {};
	timeBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	timeBufferDesc.ByteWidth = sizeof(TimeBufferType);
	timeBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	timeBufferDesc.CPUAccessFlags = 0;

	{
		HRESULT hr = m_p_dd->pDevice->CreateBuffer(&timeBufferDesc, nullptr, &m_timeBuffer);
		output_hr(hr);
		if (FAILED(hr)) {
			return codes::dx_error;
		}
	}


	// init keyboard
	m_kbd = new DirectX::Keyboard;

	// Create an EffectFactory for loading textures
	m_fxFactory = std::make_shared<DirectX::EffectFactory>(m_p_dd->pDevice);
	m_fxFactory->SetDirectory(L"C:\\Users\\chris\\source\\repos\\lol.blocks.engine\\projects\\engine\\demos\\dx11\\assets\\textures"); 

	// Load the model from .sdkmesh file
	m_datson_model = DirectX::Model::CreateFromSDKMESH(m_p_dd->pDevice, ENGINE_ASSET_DATSON_FILE_PATH, *m_fxFactory);
	m_terrain_model = DirectX::Model::CreateFromSDKMESH(m_p_dd->pDevice, ENGINE_ASSET_MOUNTIAN_FILE_PATH, *m_fxFactory);

	m_common_states = std::make_unique<DirectX::CommonStates>(m_p_dd->pDevice);

	return codes::success;
}

void engine::dx11::cube_demo::unload_content()
{

}

void engine::dx11::cube_demo::update(float dt)
{
	// Keyboard
	auto kb = m_kbd->GetState();
	float moveStep = dt * moveSpeed;

	// Movement
	if (kb.W)            m_cam.MoveForward(moveStep);
	if (kb.S)            m_cam.MoveForward(-moveStep);
	if (kb.A)            m_cam.MoveRight(-moveStep);
	if (kb.D)            m_cam.MoveRight(moveStep);
	if (kb.Space)        m_cam.MoveUp(moveStep);
	if (kb.LeftShift)    m_cam.MoveUp(-moveStep);

	// Switch mouse modes
	if (kb.Q)
	{
		m_ms->SetMode(DirectX::Mouse::MODE_RELATIVE);
	}

	if (kb.Escape)
	{
		m_ms->SetMode(DirectX::Mouse::MODE_ABSOLUTE);
	}

	m_cam.UpdateView();

	// Mouse
	auto ms = m_ms->GetState();
	float sensitivityX = static_cast<float>(ms.x) * sensitivity;
	float sensitivityY = static_cast<float>(ms.y) * sensitivity;

	// Handle camera rotation in RELATIVE mode
	if (ms.positionMode == DirectX::Mouse::MODE_RELATIVE && ms.rightButton)
	{
		m_cam.Rotate(-sensitivityY, sensitivityX);
	}

	// ---- Virtual cursor for RELATIVE mode ----
	static int virtualMouseX = m_width / 2;  // Start at center
	static int virtualMouseY = m_height /2;
	const int windowWidth = m_width;     
	const int windowHeight = m_height;    

	if (ms.positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		virtualMouseX += ms.x;
		virtualMouseY += ms.y;
		virtualMouseX = std::clamp(virtualMouseX, 0, windowWidth - 1);
		virtualMouseY = std::clamp(virtualMouseY, 0, windowHeight - 1);
	}
	else
	{
		virtualMouseX = ms.x;
		virtualMouseY = ms.y;
	}

	// Left button picking
	if (ms.leftButton)
	{
		if (mouse_collide(virtualMouseX, virtualMouseY, m_cube_vertices))
		{
			m_cube_vertices = x_move(dt * 1.05f, m_cube_vertices);
		}
	}

	// Cube rotation
	m_rotationAngle += dt;  // Rotate 1 radian per second
	if (m_rotationAngle > DirectX::XM_2PI)
		m_rotationAngle -= DirectX::XM_2PI;

	m_timeData.gTime += dt;

}

void engine::dx11::cube_demo::render()
{
	if (m_p_dd->pImmediateContext == nullptr)
		return;

	m_p_dd->pImmediateContext->OMSetRenderTargets(1, &m_p_rtv, m_p_dsv);


	float clear_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_p_dd->pImmediateContext->ClearRenderTargetView(m_p_rtv, clear_color);
	
	// Clear depth buffer 
	m_p_dd->pImmediateContext->ClearDepthStencilView(m_p_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	// Set blend, rasterizer, depth states
	m_p_dd->pImmediateContext->OMSetBlendState(m_common_states->Opaque(), nullptr, 0xFFFFFFFF);
	m_p_dd->pImmediateContext->RSSetState(m_common_states->CullCounterClockwise());
	m_p_dd->pImmediateContext->OMSetDepthStencilState(m_common_states->DepthDefault(), 0);

	unsigned int stride = sizeof(DirectX::XMFLOAT3);
	unsigned int offset = 0;

	m_p_dd->pImmediateContext->IASetInputLayout(m_il);
	
	// spins the world
	// DirectX::XMMATRIX world = DirectX::XMMatrixRotationY(m_rotationAngle);
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();

	CameraBuffer cb = {};
	cb.world = DirectX::XMMatrixTranspose(world);
	cb.view = DirectX::XMMatrixTranspose(m_cam.GetViewMatrix());
	cb.projection = DirectX::XMMatrixTranspose(m_cam.GetProjectionMatrix());
	m_p_dd->pImmediateContext->UpdateSubresource(m_cameraCB, 0, nullptr, &cb, 0, 0);
	

	
	m_p_dd->pImmediateContext->UpdateSubresource(m_timeBuffer, 0, nullptr, &m_timeData, 0, 0);

	m_p_dd->pImmediateContext->PSSetConstantBuffers(0, 1, &m_timeBuffer);
	m_p_dd->pImmediateContext->VSSetConstantBuffers(0, 1, &m_cameraCB);
	m_p_dd->pImmediateContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	m_p_dd->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_p_dd->pImmediateContext->VSSetShader(m_sc_vs, 0, 0);
	m_p_dd->pImmediateContext->PSSetShader(m_sc_ps, 0, 0);
	m_p_dd->pImmediateContext->Draw(static_cast<UINT>(m_cube_vertices.size()), 0);

	m_datson_model->Draw(m_p_dd->pImmediateContext, *m_common_states, world, m_cam.GetViewMatrix(), m_cam.GetProjectionMatrix());
	m_terrain_model->Draw(m_p_dd->pImmediateContext, *m_common_states, world, m_cam.GetViewMatrix(), m_cam.GetProjectionMatrix());

	m_p_dd->pSwapChain->Present(1, 0);
}

void engine::dx11::cube_physics::update(float dt) {
	cube_demo::update(dt);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = m_p_dd->pImmediateContext->Map(m_vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (SUCCEEDED(hr))
	{
		// Copy updated vertex data from CPU to GPU
		memcpy(mappedResource.pData, m_cube_vertices.data(), m_cube_vertices.size() * sizeof(DirectX::XMFLOAT3));

		// Unlock the buffer
		m_p_dd->pImmediateContext->Unmap(m_vb, 0);
	}
}

void engine::dx11::cube_physics::render()
{
	cube_demo::render();
}
