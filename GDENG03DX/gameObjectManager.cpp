#include "gameObjectManager.h"

#include <iostream>

#include "graphicsEngine.h"
#include "deviceContext.h"
#include "gameObject.h"
#include "pixelShader.h"
#include "serializer.h"
#include "vertexShader.h"

gameObjectManager::gameObjectManager()
{
}

gameObjectManager* gameObjectManager::get() {
	static gameObjectManager game_object_manager;
	return &game_object_manager;
}

gameObject* gameObjectManager::findObjectByName(std::string name)
{
	return m_game_object_table[name];
}

std::vector<gameObject*> gameObjectManager::getAllObjects()
{
	return m_game_object_list;
}

std::vector<gameObject*>* gameObjectManager::getGameObjectList()
{
	return &m_game_object_list;
}

void gameObjectManager::addObject(gameObject* game_object)
{
	std::cout << game_object->getName() << " added" << std::endl;
	m_game_object_table[game_object->getName()] = game_object;
	m_game_object_list.push_back(game_object);
	game_object->init();
}

void gameObjectManager::deleteObject(std::string name)
{
	// find game object from game object list
	for (int i = 0; i < m_game_object_list.size(); i++)
	{	// remove from list
		if (m_game_object_list[i]->getName() == name)
			m_game_object_list.erase(m_game_object_list.begin() + i);
	}

	m_game_object_table[name]->release();	// release game object
	m_game_object_table.erase(name);	// remove from table
}

void gameObjectManager::deleteObject(gameObject* game_object)
{	
	deleteObject(game_object->getName());
}

void gameObjectManager::deleteAllObjects()
{
	// clear object table
	m_game_object_table.clear();
	// release objects in game object list
	for (auto& game_object : m_game_object_list)
	{	// 
		game_object->release();
	}
	// clear game object list
	m_game_object_list.clear();
}

void gameObjectManager::update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left)
{
	for (auto& game_object : m_game_object_list)
	{
		game_object->update(world_camera_temp, top, bottom, right, left);
	}
}

void gameObjectManager::draw(vertexShader* vertex_shader, pixelShader* pixel_shader)
{
	for (auto& game_object : m_game_object_list)
	{
		graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertex_shader, game_object->getConstantBuffer()); // set constant buffer to object constant buffer
		graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixel_shader, game_object->getConstantBuffer()); // set constant buffer to object constant buffer
		game_object->draw();
	}
}

void gameObjectManager::setSelectedObject(std::string name)
{
	m_selected_object = m_game_object_table[name];
}

void gameObjectManager::setSelectedObject(gameObject* game_object)
{
	m_selected_object = game_object;
}

gameObject* gameObjectManager::getSelectedObject()
{
	return m_selected_object;
}

void gameObjectManager::deselectObject()
{
	m_selected_object = nullptr;
}

void gameObjectManager::reloadScene()
{
	deleteAllObjects();
	serializer::openScene(m_current_scene_filepath);
	m_isFirstPlay = false;
}

bool gameObjectManager::getFirstPlay()
{
	return m_isFirstPlay;
}

void gameObjectManager::firstPlay()
{
	serializer::saveScene(m_current_scene_filepath);
	m_isFirstPlay = true;	
}
