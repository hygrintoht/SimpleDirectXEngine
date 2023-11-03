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

	void addObject(gameObject* game_object);
	void deleteObject(std::string name);
	void deleteAllObjects();

	void updateInput();
	void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left);
	void draw(vertexShader* vertex_shader, pixelShader* pixel_shader);

private:
	gameObjectManager();

	std::unordered_map<std::string, gameObject*> m_game_object_table;
	std::vector<gameObject*> m_game_object_list;
};