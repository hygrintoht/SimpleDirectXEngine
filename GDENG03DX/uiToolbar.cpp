#include "uiToolbar.h"

#include "gameObjectManager.h"
#include "graphicsEngine.h"
#include "meshObject.h"
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
			if (ImGui::MenuItem("Create Cube"))
			{
				auto* mesh_object = new meshObject("createdCube");
				mesh_object->loadObjFileData("cube.obj");
				mesh_object->setPosition(vector3(0,0,0));
				mesh_object->setScale(vector3(1.0f, 1.0f, 1.0f));
				mesh_object->changeAnimationType(-1);

				

				gameObjectManager::get()->addObject(mesh_object);
			}
			if (ImGui::MenuItem("Create Sphere"))
			{
				
			}
			if (ImGui::MenuItem("Create Plane"))
			{
				
			}
			if (ImGui::MenuItem("Create Light")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
