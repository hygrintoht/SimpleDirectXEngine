#pragma once
#include <d3d11.h>

class deviceContext;

class swapChain
{
public:
	swapChain();
	~swapChain();

	bool init(HWND hwnd, UINT width, UINT height);
	bool release();

	IDXGISwapChain* getSwapChain();
	bool present(bool vsync);

	ID3D11ShaderResourceView* m_texture_shader_resource_view;

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target_view;
	ID3D11DepthStencilView* m_depth_stencil_view;

	ID3D11SamplerState* m_sampler_state;

	friend class deviceContext;
};

 