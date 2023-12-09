#pragma once
#include "uiScreenAbstract.h"

class uiEngineProfiler : public uiScreenAbstract
{
protected:
	uiEngineProfiler(std::string name) : uiScreenAbstract(name) {}
	~uiEngineProfiler();

	void drawUI() override;

	friend class uiManager;

private:
	bool m_tool_active = false;

	//float m_average_frame_time = 0;
	//float m_average_fps = 0;

	std::string m_average_frame_time_string;
	std::string m_average_fps_string;
};
