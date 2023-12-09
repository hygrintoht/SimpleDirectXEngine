#include "uiEngineProfiler.h"

#include <iostream>

#include "engineTime.h"
#include "Imgui/imgui.h"

void uiEngineProfiler::drawUI()
{
	
	//m_average_frame_time = (m_average_frame_time + engineTime::get()->getDeltaTime()) / 2.0f;
	//m_average_fps = 1.0f / m_average_frame_time;

	if (!engineTime::get()->isPaused())
	{
		m_average_frame_time_string = "average frame time: " + std::to_string(engineTime::get()->getAverageFrameTime());//m_average_frame_time);
		m_average_fps_string = "average fps: " + std::to_string(engineTime::get()->getAverageFPS());
	}
	if (m_active)
	{
		ImGui::Begin("Engine Profiler", &m_tool_active, ImGuiWindowFlags_None);
		ImGui::Text(m_average_frame_time_string.c_str());
		ImGui::Text(m_average_fps_string.c_str());
		ImGui::End();
	}
}
