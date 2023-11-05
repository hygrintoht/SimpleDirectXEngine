#include "uiInspector.h"

#include "Imgui/imgui.h"

void uiInspector::drawUI()
{
	ImGui::Begin("Inspector", &m_tool_active, ImGuiWindowFlags_None);
	ImGui::Text("No object selected.Select an object from the scene.");
	ImGui::End();
}
