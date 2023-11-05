#pragma once
#include "uiScreenAbstract.h"

class uiToolbar : public uiScreenAbstract
{
protected:
	uiToolbar(std::string name) : uiScreenAbstract(name) {}
	~uiToolbar();

	void drawUI() override;

	friend class uiManager;
};
