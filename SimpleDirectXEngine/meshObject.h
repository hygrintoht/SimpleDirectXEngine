#pragma once

#include "tinyobjloader/tiny_obj_loader.h"

#include "gameObject.h"
#include "string"
#include "vector"

class meshObject : public gameObject
{
public:
	meshObject();
	meshObject(std::string name);
	meshObject(std::string name, std::string file_path);
	~meshObject() override;

	void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left) override;

	void loadObjFileData(std::string file_path);
	void loadObjDataToMemory();

	std::string getFilePath();
	void changeAnimationType(int animation);

private:
	tinyobj::attrib_t* attrib = new tinyobj::attrib_t;	// obj atributes
	std::vector<tinyobj::shape_t>* shapes = new std::vector<tinyobj::shape_t>;	// list of shapes

	std::string m_file_path;

	int m_animation_type = 0;
	float m_animation_timer = 0;
	int m_animation_direction = 1;
};
