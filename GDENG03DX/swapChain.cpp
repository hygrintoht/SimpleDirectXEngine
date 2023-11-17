#include "swapChain.h"
#include "graphicsEngine.h"

swapChain::swapChain()
{
}

swapChain::~swapChain()
{
}


bool swapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = graphicsEngine::get()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = graphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
		return false;

	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
		return false;

	D3D11_TEXTURE2D_DESC p_desc;
	buffer->GetDesc(&p_desc);

	hr = device->CreateRenderTargetView(buffer, NULL, &m_render_target_view);

	if (FAILED(hr))
		return false;

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(buffer, NULL, &m_texture_shader_resource_view);

	if (FAILED(hr))
		return false;

	buffer->Release();

	D3D11_TEXTURE2D_DESC depthDesc;
	depthDesc.Width = width;
	depthDesc.Height = height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthDesc, NULL, &buffer);

	if (FAILED(hr))
		return false;

	hr = device->CreateDepthStencilView(buffer, NULL, &m_depth_stencil_view);
	buffer->Release();

	if (FAILED(hr))
		return false;

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;  
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;      
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;      
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;      
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;   
	samplerDesc.MinLOD = 0;                                 
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&samplerDesc, &m_sampler_state);

	if (FAILED(hr))
		return false;

	return true;
}


bool swapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

IDXGISwapChain* swapChain::getSwapChain()
{
	return m_swap_chain;
}

bool swapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}
