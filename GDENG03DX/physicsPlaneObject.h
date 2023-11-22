#pragma once
#include "meshObject.h"

class physicsPlaneObject : public meshObject
{
public:
	physicsPlaneObject(std::string name, bool skipInit = false);
	~physicsPlaneObject();

	void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left) override;

protected:
	float mass = 1000.0f;
};