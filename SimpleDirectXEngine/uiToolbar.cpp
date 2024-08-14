#include "uiToolbar.h"

#include "Imgui/imgui.h"

#include "engineTime.h"
#include "eventHistoryManager.h"
#include "gameObjectManager.h"
#include "graphicsEngine.h"
#include "meshObject.h"
#include "physicsComponent.h"
#include "physicsMeshObject.h"
#include "physicsPlaneObject.h"
#include "serializer.h"
#include "uiManager.h"
#include "unitySerializer.h"

void uiToolbar::drawUI()
{
	const uiNames ui_names;

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
			}
			if (ImGui::MenuItem("Open"))
			{
				gameObjectManager::get()->deleteAllObjects();
				serializer::openScene();
			}
			if (ImGui::MenuItem("Save as Unity Json Format"))
			{
				unitySerializer::save();
			}
			if (ImGui::MenuItem("Load as Unity Json Format"))
			{
				gameObjectManager::get()->deleteAllObjects();
				unitySerializer::open();
			}
			if (ImGui::MenuItem("Exit"))
			{
				exit(0);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo"))
			{
				eventHistoryManager::get()->undo();
			}
			if (ImGui::MenuItem("Redo"))
			{
				eventHistoryManager::get()->redo();
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
			if (ImGui::MenuItem("create PhysicsCube"))
			{
				for (int i = 0; i < 1; i++)
				{
					auto* physics_object = new physicsMeshObject("createdPhysicsCube" + std::to_string(objectCounter));
					objectCounter++;

					gameObjectManager::get()->addObject(physics_object);

					void* shader_byte_code = nullptr;
					size_t size_shader = 0;

					graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

					physics_object->loadVertexBuffer(shader_byte_code, size_shader);
				}
			}
			if (ImGui::MenuItem("create PhysicsCubes"))
			{
				for (int i = 0; i < 5; i++)
				{
					vector3 position = vector3(randFNOneToOne() * 4.0f, randFNOneToOne() * 2 - 2.0f, randFNOneToOne() * 4.0f);
					auto* physics_cube = new physicsMeshObject("createdPhysicsCube" + std::to_string(objectCounter), position, vector3(1.0f, 1.0f, 1.0f), vector3(0, 0, 0));

					physicsComponent* component = (physicsComponent*)physics_cube->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
					component->setMass(1);

					gameObjectManager::get()->addObject(physics_cube);

					void* shader_byte_code = nullptr;
					size_t size_shader = 0;

					graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

					physics_cube->loadVertexBuffer(shader_byte_code, size_shader);
				}
			}
			if (ImGui::MenuItem("create PhysicsPlane"))
			{
				auto* physics_object = new physicsPlaneObject("createdPhysicsPlane" + std::to_string(objectCounter));
				objectCounter++;

				physicsComponent* component = (physicsComponent*)physics_object->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
				component->getRigidBody()->setType(BodyType::KINEMATIC);

				gameObjectManager::get()->addObject(physics_object);

				void* shader_byte_code = nullptr;
				size_t size_shader = 0;

				graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

				physics_object->loadVertexBuffer(shader_byte_code, size_shader);
			}


			if (ImGui::MenuItem("Create Light")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Play/Pause"))
		{
			if (ImGui::MenuItem("Play"))
			{	// if first play
				if (!gameObjectManager::get()->getFirstPlay())
				{	
					gameObjectManager::get()->firstPlay();	// set as first play
					engineTime::get()->togglePause();	// toggle from pause
				}
				else if(gameObjectManager::get()->getFirstPlay()) // if play is pressed again
				{
					gameObjectManager::get()->reloadScene(); // reload scene
					if(!engineTime::get()->isPaused())	// if scene is running
					{
						engineTime::get()->togglePause(); // toggle pause
					}
				}
			}
			if (ImGui::MenuItem("Pause"))
			{	// if first play
				if(gameObjectManager::get()->getFirstPlay())
					engineTime::get()->togglePause();
			}
			if (ImGui::MenuItem("Time Step"))
			{
				if(engineTime::get()->isPaused())
				{	// time step
					
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Show UI Windows"))
		{
			if (ImGui::MenuItem(ui_names.PROFILER_SCREEN.c_str()))
			{
				uiManager::get()->toggleUIScreen(ui_names.PROFILER_SCREEN);
			}
			if (ImGui::MenuItem(ui_names.INSPECTOR_SCREEN.c_str()))
			{
				uiManager::get()->toggleUIScreen(ui_names.INSPECTOR_SCREEN);
			}
			if (ImGui::MenuItem(ui_names.HIERARCHY_SCREEN.c_str()))
			{
				uiManager::get()->toggleUIScreen(ui_names.HIERARCHY_SCREEN);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
