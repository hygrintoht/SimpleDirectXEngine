#include "uiToolbar.h"

#include "gameObjectManager.h"
#include "graphicsEngine.h"
#include "meshObject.h"
#include "serializer.h"
#include "Imgui/imgui.h"

void uiToolbar::drawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{
				gameObjectManager::get()->deleteAllObjects();
			}
			if (ImGui::MenuItem("Save"))
			{
				serializer::saveScene();
				// serialize all game objects to the text(json) file
			}
			if (ImGui::MenuItem("Open"))
			{
				// parse all game objects from text file to the game scene
			}
			if (ImGui::MenuItem("Exit"))
			{
				exit(0); // kill program
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object"))
		{
			if (ImGui::MenuItem("Create Cube"))
			{
				auto* mesh_object = new meshObject("createdCube" + std::to_string(objectCounter));
				objectCounter++;
				mesh_object->loadObjFileData("cube.obj");
				mesh_object->setPosition(vector3(0,0,0));
				mesh_object->setScale(vector3(1.0f, 1.0f, 1.0f));
				mesh_object->changeAnimationType(-1);

				gameObjectManager::get()->addObject(mesh_object);

				void* shader_byte_code = nullptr;
				size_t size_shader = 0;

				graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

				mesh_object->loadVertexBuffer(shader_byte_code, size_shader);
			}
			if (ImGui::MenuItem("Create Sphere"))
			{
				auto* mesh_object = new meshObject("createdSphere" + std::to_string(objectCounter));
				objectCounter++;
				mesh_object->loadObjFileData("sphere.obj");
				mesh_object->setPosition(vector3(0, 0, 0));
				mesh_object->setScale(vector3(1.0f, 1.0f, 1.0f));
				mesh_object->changeAnimationType(-1);

				gameObjectManager::get()->addObject(mesh_object);

				void* shader_byte_code = nullptr;
				size_t size_shader = 0;

				graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

				mesh_object->loadVertexBuffer(shader_byte_code, size_shader);
			}
			if (ImGui::MenuItem("Create Plane"))
			{
				auto* mesh_object = new meshObject("createdPlane" + std::to_string(objectCounter));
				objectCounter++;
				mesh_object->loadObjFileData("plane.obj");
				mesh_object->setPosition(vector3(0, 0, 0));
				mesh_object->setScale(vector3(10.0f, 10.0f, 10.0f));
				mesh_object->changeAnimationType(-1);

				gameObjectManager::get()->addObject(mesh_object);

				void* shader_byte_code = nullptr;
				size_t size_shader = 0;

				graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

				mesh_object->loadVertexBuffer(shader_byte_code, size_shader);
			}
			if (ImGui::MenuItem("Create Light")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
