#include "physicsMeshObject.h"

#include "physicsComponent.h"

physicsMeshObject::physicsMeshObject(std::string name, bool skipInit) : meshObject(name, "cube.obj")
{
	setPosition(vector3(0.0f, 5.0f, 0.0f));
	setScale(vector3(1.0f, 1.0f, 1.0f));
	//this->updateLocalMatrix();
	changeAnimationType(-1);
	this->attachComponent(new physicsComponent("PhysicsComponent", this));
}

physicsMeshObject::~physicsMeshObject()
{
	meshObject::~meshObject();
}


void physicsMeshObject::update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left)
{
	meshObject::update(world_camera_temp, top, bottom, right, left);
}