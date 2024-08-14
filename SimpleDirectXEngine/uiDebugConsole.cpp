#include "uiDebugConsole.h"

#include "baseComponentSystem.h"
#include "debugLog.h"
#include "Imgui/imgui.h"

void uiDebugConsole::drawUI()
{
	ImGui::Begin("Debug Console", &m_tool_active, ImGuiWindowFlags_None);
	if(ImGui::Button("Generate Log"))
	{
		debugLog::get()->addLog("wow");
	}
	ImGui::SameLine();
	if(ImGui::Button("Clear Log"))
	{
		debugLog::get()->clearLog();
	}
	ImGui::SameLine();
	if (ImGui::Button("Time Step"))
	{
		baseComponentSystem::get()->getPhysicsSystem()->timeStep();
	}
	for(std::string log : debugLog::get()->m_log_list)
	{
		ImGui::Text(log.c_str());
	}
	ImGui::End();
}
