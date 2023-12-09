#pragma once
#include "meshObject.h"

class physicsPlaneObject : public meshObject
{
public:
	physicsPlaneObject(std::string name);
	physicsPlaneObject(std::string name, vector3 position, vector3 scale, vector3 rotation);
	physicsPlaneObject(std::string name, vector3 position, vector3 scale, quaternion rotation);
	~physicsPlaneObject();

	void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left) override;

protected:
	float mass = 1000.0f;
};