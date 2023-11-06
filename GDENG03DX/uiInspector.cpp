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
		if (m_current_object_string != game_object->getName())
		{
			vector3 current_position = game_object->m_transform.getTranslation();
			m_position[0] = current_position.m_x;
			m_position[1] = current_position.m_y;
			m_position[2] = current_position.m_z;
		}
		std::string name_string = "Name: " + game_object->getName();
		ImGui::Text(name_string.c_str());

		ImGui::DragFloat3("Position: ", m_position, 0.1f);
		ImGui::DragFloat3("Rotation: ", m_rotation, 0.1f);
		ImGui::DragFloat3("Scale: ", m_scale, 0.1f);

		vector3 vec = vector3(m_position[0], m_position[1], m_position[2]);
		game_object->setPosition(vec);
		game_object->setRotation(vector3(m_rotation[0], m_rotation[1], m_rotation[2]));
		game_object->setScale(vector3(m_scale[0], m_scale[1], m_scale[2]));

	}
	ImGui::End();
	
}
