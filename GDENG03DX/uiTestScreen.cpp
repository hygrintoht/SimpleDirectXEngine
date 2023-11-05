#include "uiTestScreen.h"

#include "engineTime.h"
#include "Imgui/imgui.h"

void uiTestScreen::drawUI()
{
	ImGui::Begin("Scene Settings", &m_tool_active, ImGuiWindowFlags_None);
	ImGui::Text("Below are settings for configuring the scene");
	ImGui::Checkbox("Show demo window", &m_demo_window_active);
	ImGui::ColorEdit4("clear color", m_clear_color);
	if (ImGui::Button("pause animation"))
	{
		engineTime::get()->togglePause();
	}
	ImGui::End();

	if (m_demo_window_active)
		ImGui::ShowDemoWindow(); // Show demo window
}
