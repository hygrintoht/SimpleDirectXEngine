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

	//bool m_enter_pressed = false;
	//int test = 0;
	float m_massUpdate = 1000.0f;


	bool m_was_manupulated = false;

	std::string m_current_object_string = "";
};
