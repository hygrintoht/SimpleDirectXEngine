#pragma once
#include "uiScreenAbstract.h"

class uiWorldOutliner: public uiScreenAbstract
{
protected:
	uiWorldOutliner(std::string name) : uiScreenAbstract(name) {}
	~uiWorldOutliner();

	void drawUI() override;

	friend class uiManager;

private:
	bool m_tool_active = false;
};
