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

	void genereateSceneTexture();
	ID3D11ShaderResourceView* getSceneTexture();

	
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target_view;
	ID3D11DepthStencilView* m_depth_stencil_view;

	//ID3D11RenderTargetView* m_offscreen_render_target_view;
	ID3D11ShaderResourceView* m_scene_shader_resource_view;

	//ID3D11SamplerState* m_sampler_state;

	ID3D11Texture2D* renderTargetTexture = NULL;
	ID3D11Texture2D* sceneTexture = NULL;

	friend class deviceContext;
};

 