#pragma once
#include "uiScreenAbstract.h"

class uiDebugConsole : public uiScreenAbstract
{
protected:
	uiDebugConsole(std::string name) : uiScreenAbstract(name) {}
	~uiDebugConsole() = default;

	void drawUI() override;

	friend class uiManager;
	
private:
	bool m_tool_active = false;
};