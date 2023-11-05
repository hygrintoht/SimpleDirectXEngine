#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "matrix4x4.h"

class gameObject;
class vertexShader;
class pixelShader;

class gameObjectManager
{
public:
	static gameObjectManager* get();

	// retrieval
	gameObject* findObjectByName(std::string name); 
	std::vector<gameObject*> getAllObjects();
	std::vector<gameObject*>* getGameObjectList();
	// status
	int activeObjects();
	// storage operations
	void addObject(gameObject* game_object);
		//void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
	void deleteObject(std::string name);
	void deleteObject(gameObject* game_object);
	void deleteAllObjects();
	// update operations
		//void updateInput();
	void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left); // to be used for multiple cameras
	void draw(vertexShader* vertex_shader, pixelShader* pixel_shader);
	// object selection
	void setSelectedObject(std::string name);
	void setSelectedObject(gameObject* game_object);
	gameObject* getSelectedObject();

private:
	gameObjectManager();

	std::unordered_map<std::string, gameObject*> m_game_object_table;
	std::vector<gameObject*> m_game_object_list;

	std::vector<gameObject> m_game_objects; // used 

	gameObject* m_selected_object = nullptr;
};