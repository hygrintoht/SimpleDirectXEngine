#pragma once
#include "uiScreenAbstract.h"
#include <string>

class uiInspector : public uiScreenAbstract
{
protected:
	uiInspector(std::string name) : uiScreenAbstract(name) {}
	~uiInspector() {};

	void drawUI() override;

	friend class uiManager;

private:
	bool m_tool_active = false;

	float m_position[3] = { 0 };
	float m_rotation[3] = { 0 };
	float m_scale[3] = { 1.0f, 1.0f, 1.0f };

	std::string m_current_object_string = "";
};
