#include "unitySerializer.h"

#include <fstream>
#include <iostream>

#include "debugLog.h"
#include "gameObjectManager.h"
#include "graphicsEngine.h"
#include "matrix4x4.h"
#include "meshObject.h"
#include "physicsPlaneObject.h"
#include "vector3.h"
#include "json/json.h"
#include "physicsComponent.h"
#include "physicsMeshObject.h"
#include "quaternion.h"
#include "uiManager.h"

void unitySerializer::save()
{

	std::vector<gameObject*> game_objects = gameObjectManager::get()->getAllObjects();

	Json::Value json_scene;
	// for each game object in scene
	for (auto& game_object : game_objects)
	{
		// set json game object type and name
		Json::Value json_game_object;
		json_game_object["type"] = game_object->getUnityType();
		json_game_object["name"] = game_object->getName();
		// get game object transform data
		vector3 _position = game_object->m_transform.getTranslation();
		vector3 _scale = game_object->m_transform.getScale();
		quaternion _rotation = quaternion::fromRotationMatrix(game_object->m_transform);
		_rotation = _rotation.normalize();
		vector3 _eulerAngles = quaternion::quaternionToEulerAngles(_rotation);
		// create json values for vectors and quaternion
		Json::Value jsonPosition;
		Json::Value jsonScale;
		Json::Value jsonRotation;
		Json::Value jsonEuler;
		// append data to json values
		jsonPosition.append(_position.m_x);
		jsonPosition.append(_position.m_y);
		jsonPosition.append(_position.m_z);

		jsonScale.append(_scale.m_x);
		jsonScale.append(_scale.m_y);
		jsonScale.append(_scale.m_z);

		jsonRotation.append(_rotation.m_w);
		jsonRotation.append(_rotation.m_x);
		jsonRotation.append(_rotation.m_y);
		jsonRotation.append(_rotation.m_z);

		jsonEuler.append(_eulerAngles.m_x);
		jsonEuler.append(_eulerAngles.m_y);
		jsonEuler.append(_eulerAngles.m_z);
		// set json game object vectors and quaternion
		json_game_object["position"] = jsonPosition;
		json_game_object["scale"] = jsonScale;
		json_game_object["rotation"] = jsonRotation;
		json_game_object["euler"] = jsonEuler;
		// check if object is a physics cube
		if(game_object->getUnityType() == gameObject::unityGameObjectType::physics_cube_object)
		{	// get mass from physics object
			physicsComponent* _physicsComponent = (physicsComponent*)game_object->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
			float jsonMass = _physicsComponent->getMass();
			// set json object mass
			json_game_object["mass"] = jsonMass;
		}
		else // if not a physics cube
		{	// set default mass as 1
			json_game_object["mass"] = 1;
		}
		json_scene["thing"].append(json_game_object);
	}

	std::string filepath;

	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = uiManager::get()->getWindowHandle();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(*szFile);
	//ofn.lpstrFilter = L"JSON Scene File (*.json) \0 *.json\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn))
	{
		std::wstring filepathW = szFile;
		filepath = std::string(filepathW.begin(), filepathW.end());
	}

	// build string
	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, json_scene);

	// create file stream
	//std::ofstream file("ge_test.json");
	std::ofstream file(filepath);

	// open file
	if (!file.is_open()) {
		std::cout << "error opening file" << std::endl;
		return;
	}
	// write to file
	file << jsonString;
	file.close();
	// log
	debugLog::get()->addLog("unity scene saved");
	/*
	std::vector<gameObject*> game_objects = gameObjectManager::get()->getAllObjects();

	Json::Value json_scene;

	for (auto& game_object : game_objects)
	{
		Json::Value json_game_object; // hold a data of the current game object
		// game object attributes
		json_game_object["name"] = game_object->getName();
		json_game_object["type"] = game_object->getType(); // update type

		Json::Value jsonPosition;
		Json::Value jsonScale;
		Json::Value jsonRotation;

		jsonPosition.append(game_object->m_transform.getTranslation().m_x);
		jsonPosition.append(game_object->m_transform.getTranslation().m_y);
		jsonPosition.append(game_object->m_transform.getTranslation().m_z);

		jsonScale.append(game_object->m_transform.getScale().m_x);
		jsonScale.append(game_object->m_transform.getScale().m_y);
		jsonScale.append(game_object->m_transform.getScale().m_z);

		quaternion quat = quaternion::fromRotationMatrix(game_object->m_transform);

		vector3 eulerAngles = quaternion::quaternionToEulerAngles(quat);

		jsonScale.append(eulerAngles.m_x);
		jsonScale.append(eulerAngles.m_y);
		jsonScale.append(eulerAngles.m_z);

		json_game_object["position"].append(jsonPosition);
		json_game_object["scale"].append(jsonScale);
		json_game_object["rotation"].append(jsonRotation);

		json_scene["thing"].append(json_game_object);s
	}

	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, json_scene);

	std::ofstream file("test.json");


	if (!file.is_open()) {
		std::cout << "Error opening file for writing!" << std::endl;
		return;
	}

	file << jsonString;
	file.close();
	*/
}

void unitySerializer::open()
{	// create file stream

	std::string filepath;

	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = uiManager::get()->getWindowHandle();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(*szFile);
	//ofn.lpstrFilter = L"JSON Scene File (*.json) \0 *.json\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		std::wstring filepathW = szFile;
		filepath = std::string(filepathW.begin(), filepathW.end());
	}

	//std::ifstream file("ge_test.json");
	std::ifstream file(filepath);
	// open file
	if (!file.is_open())
	{
		std::cout << "failed to open file" << std::endl;
		return;
	}
	// create root object
	Json::Value root;
	// read from file
	file >> root;
	file.close();
	// extract thing list from root
	const Json::Value jsonThingList = root["thing"];
	// for each thing in thing list
	for (const Json::Value& jsonThing : jsonThingList)
	{	// extract type name and mass
		auto type = static_cast<gameObject::unityGameObjectType>(jsonThing["type"].asInt());
		std::string name = jsonThing["name"].asString();
		float mass = jsonThing["mass"].asFloat();
		// create json values for transform data
		Json::Value jsonPosition = jsonThing["position"];
		Json::Value jsonScale = jsonThing["scale"];
		Json::Value jsonRotation = jsonThing["rotation"];
		Json::Value jsonEuler = jsonThing["euler"];
		// create vectors and quaternion
		vector3 position;
		vector3 scale;
		quaternion rotation;
		vector3 euler;
		// extract transform data
		position.m_x = jsonPosition[0].asFloat();
		position.m_y = jsonPosition[1].asFloat();
		position.m_z = jsonPosition[2].asFloat();

		scale.m_x = jsonScale[0].asFloat();
		scale.m_y = jsonScale[1].asFloat();
		scale.m_z = jsonScale[2].asFloat();

		rotation.m_w = jsonRotation[0].asFloat();
		rotation.m_x = jsonRotation[1].asFloat();
		rotation.m_y = jsonRotation[2].asFloat();
		rotation.m_z = jsonRotation[3].asFloat();

		euler.m_x = jsonEuler[0].asFloat();
		euler.m_y = jsonEuler[1].asFloat();
		euler.m_z = jsonEuler[2].asFloat();
		// create shader holder
		void* shader_byte_code = nullptr;
		size_t size_shader = 0;
		// generate object of type
		if (type == gameObject::unityGameObjectType::cube_object)
		{
			auto* mesh_object = new meshObject(name);
			mesh_object->loadObjFileData("cube.obj");
			
			mesh_object->setPosition(position);
			mesh_object->setScale(scale);
			mesh_object->setRotation(rotation);
			
			//mesh_object->setMatrix(position, scale, rotation);

			mesh_object->changeAnimationType(-1);

			gameObjectManager::get()->addObject(mesh_object);

			graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

			mesh_object->loadVertexBuffer(shader_byte_code, size_shader);
		}
		if (type == gameObject::unityGameObjectType::physics_plane_object)
		{
			auto* physics_plane = new physicsPlaneObject(name, position, scale, euler);

			physicsComponent* component = (physicsComponent*)physics_plane->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
			component->getRigidBody()->setType(BodyType::KINEMATIC);

			gameObjectManager::get()->addObject(physics_plane);

			graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

			physics_plane->loadVertexBuffer(shader_byte_code, size_shader);
		}
		if (type == gameObject::unityGameObjectType::physics_cube_object)
		{
			auto* physics_cube = new physicsMeshObject(name, position, scale, euler);

			physicsComponent* component = (physicsComponent*)physics_cube->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
			component->setMass(mass);

			gameObjectManager::get()->addObject(physics_cube);

			graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

			physics_cube->loadVertexBuffer(shader_byte_code, size_shader);
		}
	}

	/*
	std::ifstream file("test.json");

	if (!file.is_open())
	{
		std::cout << "failed to open file" << std::endl;
		return;
	}

	Json::Value root;
	file >> root;
	file.close();

	const Json::Value jsonThingList = root["thing"];

	for (const Json::Value& jsonThing : jsonThingList)
	{
		// parsing json data
		int type = jsonThing["type"].asInt();
		std::string name = jsonThing["name"].asString();
		float mass = jsonThing["mass"].asFloat();

		Json::Value jsonPosition = jsonThing["position"];
		Json::Value jsonScale = jsonThing["scale"];
		Json::Value jsonRotation = jsonThing["rotation"];

		vector3 position;
		vector3 scale;
		vector3 rotation;
		
		position.m_x = jsonPosition[0].asFloat();
		position.m_y = jsonPosition[1].asFloat();
		position.m_z = jsonPosition[2].asFloat();
		scale.m_x = jsonScale[0].asFloat();
		scale.m_y = jsonScale[1].asFloat();
		scale.m_z = jsonScale[2].asFloat();
		rotation.m_x = jsonRotation[0].asFloat();
		rotation.m_y = jsonRotation[1].asFloat();
		rotation.m_z = jsonRotation[2].asFloat();
		
		void* shader_byte_code = nullptr;
		size_t size_shader = 0;

		if(type == 0)
		{
			auto* mesh_object = new meshObject(name);
			mesh_object->loadObjFileData("cube.obj");
			mesh_object->setPosition(position);
			mesh_object->setScale(scale);
			mesh_object->setRotation(rotation);

			mesh_object->changeAnimationType(-1);

			gameObjectManager::get()->addObject(mesh_object);

			graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

			mesh_object->loadVertexBuffer(shader_byte_code, size_shader);
		}
		if(type == 1)
		{
			auto* physics_plane = new physicsPlaneObject(name, position, scale, rotation);

			physicsComponent* component = (physicsComponent*)physics_plane->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
			component->getRigidBody()->setType(BodyType::KINEMATIC);

			gameObjectManager::get()->addObject(physics_plane);

			graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

			physics_plane->loadVertexBuffer(shader_byte_code, size_shader);
		}
		if(type == 2)
		{
			auto* physics_cube = new physicsMeshObject(name, position, scale, rotation);

			gameObjectManager::get()->addObject(physics_cube);

			graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

			physics_cube->loadVertexBuffer(shader_byte_code, size_shader);
		}
	}
	*/
}
/*
{
	"thing":
	[
		{
			"type": 2,
			"name": "test",
			"mass": 1,
			"position": [1.5, 1.5, 1.5],
			"scale": [1, 1, 1],
			"rotation": [45, 45, 45]
			"quaternion": [-0.5504099, -0.1642797, -0.5788183, -0.5788183]
		},
		{
			"type": 1,
			"name": "test2",
			"mass": 1,
			"position": [0, 0, 0],
			"scale": [2, 1, 2],
			"rotation": [0, 0, 0]
			"quaternion": [1, 0, 0, 0]
		}
	]
}
*/