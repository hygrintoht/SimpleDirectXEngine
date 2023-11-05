#pragma once
#include "uiScreenAbstract.h"

class uiInspector : public uiScreenAbstract
{
protected:
	uiInspector(std::string name) : uiScreenAbstract(name) {}
	~uiInspector();

	void drawUI() override;

	friend class uiManager;

private:
	bool m_tool_active = false;
};
