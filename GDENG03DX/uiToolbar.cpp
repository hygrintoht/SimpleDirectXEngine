#include "uiToolbar.h"

#include "Imgui/imgui.h"

void uiToolbar::drawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Save")) {}
			if (ImGui::MenuItem("Open")) {}
			if (ImGui::MenuItem("Exit")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object"))
		{
			if (ImGui::MenuItem("Create Cube")) {}
			if (ImGui::MenuItem("Create Sphere")) {}
			if (ImGui::MenuItem("Create Plane")) {}
			if (ImGui::MenuItem("Create Light")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
