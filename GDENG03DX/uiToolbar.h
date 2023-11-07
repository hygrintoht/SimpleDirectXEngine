#pragma once
#include <vector>

#include "gameObject.h"
#include "uiScreenAbstract.h"

class uiToolbar : public uiScreenAbstract
{
protected:
	uiToolbar(std::string name) : uiScreenAbstract(name) {}
	~uiToolbar();

	void drawUI() override;

	friend class uiManager;
private:
	int objectCounter = 0;
};
