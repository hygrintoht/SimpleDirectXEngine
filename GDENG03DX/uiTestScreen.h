#pragma once
#include "uiScreenAbstract.h"

class uiTestScreen : public uiScreenAbstract
{
protected:
	uiTestScreen(std::string name) : uiScreenAbstract(name) {}
	~uiTestScreen() = default;

	void drawUI() override;

	friend class uiManager;
private:
	bool m_tool_active = false;
	bool m_demo_window_active = false;
	bool m_scene_window_active = false;
	float m_clear_color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

	bool m_test_active = false;
};