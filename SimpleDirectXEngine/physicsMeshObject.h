#pragma once
#include "meshObject.h"

class physicsMeshObject : public meshObject
{
public:
	physicsMeshObject(std::string name);
	physicsMeshObject(std::string name, vector3 position, vector3 scale, vector3 rotation);
	physicsMeshObject(std::string name, vector3 position, vector3 scale, quaternion rotation);
	~physicsMeshObject();

	void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left) override;

protected:
	float mass = 1000.0f;
};
