#include "uiInspector.h"

#include "gameObject.h"
#include "Imgui/imgui.h"
#include "gameObjectManager.h"
#include "gameObject.h"

void uiInspector::drawUI()
{
	ImGui::Begin("Inspector", &m_tool_active, ImGuiWindowFlags_None);
	gameObject* game_object = gameObjectManager::get()->getSelectedObject();
	if(game_object == nullptr)
		ImGui::Text("No object selected.Select an object from the scene.");
	else
	{
		std::string name_string = "Name: " + game_object->getName();
		ImGui::Text(name_string.c_str());
	}
	ImGui::End();
}
