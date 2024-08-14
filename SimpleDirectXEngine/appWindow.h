#pragma once

#include "window.h"

#include "cubeObject.h"
#include "meshObject.h"
#include "inputListener.h"

class swapChain;
class vertexBuffer;
class indexBuffer;
class constantBuffer;
class vertexShader;
class pixelShader;

class appWindow : public window, public inputListener
{
public:
	appWindow();
	~appWindow();
	
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const point& mouse_position) override;
	virtual void onLeftMouseDown(const point& mouse_position) override;
	virtual void onLeftMouseUp(const point& mouse_position) override;
	virtual void onRightMouseDown(const point& mouse_position) override;
	virtual void onRightMouseUp(const point& mouse_position) override;
	
private:
	swapChain* m_swap_chain;
	vertexBuffer* m_vertex_buffer;
	indexBuffer* m_index_buffer;
	constantBuffer* m_constant_buffer;
	vertexShader* m_vertex_shader;
	pixelShader* m_pixel_shader;

	cubeObject test0;
	meshObject test1;
	meshObject test2;
	meshObject test3;
	meshObject test4;
	std::vector<cubeObject> m_cube_objects_list;
	int m_cube_objects_size = 50;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	//float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_right = 0.0f;
	matrix4x4 m_world_camera;

	bool m_mouse_down = false;

	//bool m_tool_active;
	//bool m_demo_window_active = false;
	float m_clear_color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	//bool m_pause_game = false;
};