#pragma once
#include "string"

class uiManager;

class uiScreenAbstract
{
protected:
	uiScreenAbstract(std::string name) : m_name(name) {}
	~uiScreenAbstract() {};

	std::string	getName() { return m_name; }
	virtual void drawUI() = 0;

	std::string m_name;

	friend class uiManager;
};
