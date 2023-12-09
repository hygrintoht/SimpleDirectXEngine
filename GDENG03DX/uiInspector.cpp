#include "uiInspector.h"

#include "baseComponentSystem.h"
#include "gameObject.h"
#include "Imgui/imgui.h"
#include "gameObjectManager.h"
#include "gameObject.h"
#include "physicsComponent.h"
#include "component.h"
#include "eventGameObjectTransform.h"
#include "eventHistoryManager.h"

void uiInspector::drawUI()
{
	if (m_active)
	{
		ImGui::Begin("Inspector", &m_tool_active, ImGuiWindowFlags_None);
		gameObject* game_object = gameObjectManager::get()->getSelectedObject();

		if (ImGui::Button("Deselect Object"))
		{
			gameObjectManager::get()->deselectObject();
		}

		if (game_object == nullptr)
			ImGui::Text("No object selected.Select an object from the scene.");
		else
		{
			if (m_current_object_string != game_object->getName() || m_was_manupulated)
			{
				m_was_manupulated = false;

				vector3 current_position = game_object->m_transform.getTranslation();
				m_position[0] = current_position.m_x;
				m_position[1] = current_position.m_y;
				m_position[2] = current_position.m_z;

				vector3 current_scale = game_object->m_transform.getScale();

				m_scale[0] = current_scale.m_x;
				m_scale[1] = current_scale.m_y;
				m_scale[2] = current_scale.m_z;

				// quaternion class needed to get euler angles so the rotation is always reset on selecting new objects
				// may be store rotation as variable?
				m_rotation[0] = 0;
				m_rotation[1] = 0;
				m_rotation[2] = 0;

				m_current_object_string = game_object->getName();
			}
			
			std::string name_string = "Name: " + game_object->getName();
			ImGui::Text(name_string.c_str());

			ImGui::DragFloat3("Position ", m_position, 0.1f);
			ImGui::InputFloat3("pIn", m_position);
			ImGui::DragFloat3("Rotation ", m_rotation, 0.1f);
			ImGui::InputFloat3("rIn", m_rotation);
			ImGui::DragFloat3("Scale ", m_scale, 0.1f);
			ImGui::InputFloat3("sIn", m_scale);

			//ImGui::Text(std::to_string(test).c_str());

			if(ImGui::IsKeyPressed(ImGuiKey_Q, true))
			{
				game_object->setPosition(vector3(m_position[0], m_position[1], m_position[2]));
				game_object->setRotation(vector3(m_rotation[0], m_rotation[1], m_rotation[2])); // set rotation is buggy
				game_object->setScale(vector3(m_scale[0], m_scale[1], m_scale[2]));
			}

			if(ImGui::IsKeyPressed(ImGuiKey_Enter, false))
			{
				m_was_manupulated = true;

				auto* event_game_object_transform = new eventGameObjectTransform(game_object, game_object->m_transform); // save current gameobject transform
				eventHistoryManager::get()->addToUndoStack(event_game_object_transform);
				// update game object transform

				game_object->setPosition(vector3(m_position[0], m_position[1], m_position[2]));
				game_object->setRotation(vector3(m_rotation[0], m_rotation[1], m_rotation[2])); // set rotation is buggy
				game_object->setScale(vector3(m_scale[0], m_scale[1], m_scale[2]));
			}

			if(ImGui::Button("Delete Object"))
			{
				gameObjectManager::get()->deleteObject(game_object);
			}

			ImGui::SeparatorText("Components");

			physicsComponent* _component = (physicsComponent*)game_object->findComponentOfType(component::componentType::Physics, "PhysicsComponent");

			if(_component != nullptr) // if component exists
			{
				if(ImGui::Button("Delete Rigid Body"))
				{
					game_object->detachComponent(_component);
					baseComponentSystem::get()->getPhysicsSystem()->unregisterComponent(_component);
					delete _component;
				}
				ImGui::Separator();
				if(_component->getGravityEnabled())
					ImGui::Text("Gravity Enabled");
				else
					ImGui::Text("Gravity Disabled");
				if(ImGui::Button("Toggle Gravity"))
				{
					_component->toggleGravity();
				}
				ImGui::InputFloat("Mass", &m_massUpdate);
				if(ImGui::Button("Update Mass"))
				{
					_component->setMass(m_massUpdate);
				}
				if(ImGui::Button("add force"))
				{
					_component->addForce();
				}
			}
			else
			{
				if (ImGui::Button("Attach Rigid Body"))
				{
					game_object->attachComponent(new physicsComponent("PhysicsComponent", game_object));
				}
			}
		}
		ImGui::End();
	}
}
