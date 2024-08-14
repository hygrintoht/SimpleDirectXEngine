#include "uiTestScreen.h"

#include "engineTime.h"
#include "graphicsEngine.h"
#include "swapChain.h"
#include "uiManager.h"
#include "Imgui/imgui.h"

void uiTestScreen::drawUI()
{
	ImGui::Begin("Scene Settings", &m_tool_active, ImGuiWindowFlags_None);
	ImGui::Text("Below are settings for configuring the scene");
	ImGui::Checkbox("Show demo window", &m_demo_window_active);
	ImGui::Checkbox("Show scene window", &m_scene_window_active);
	ImGui::ColorEdit4("clear color", m_clear_color);
	if (ImGui::Button("pause animation"))
	{
		engineTime::get()->togglePause();
	}
	ImGui::End();
	if (m_scene_window_active)
	{
		ImGui::Begin("Image Test", &m_test_active, ImGuiWindowFlags_None);
		ImTextureID my_tex_id = uiManager::get()->getSwapChain()->getSceneTexture();

		float my_tex_w = 1024.0f;
		float my_tex_h = 768.0f;
		ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
		ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
		ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);

		ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h));

		ImGui::End();
	}
	if (m_demo_window_active)
		ImGui::ShowDemoWindow(); // Show demo window
}
