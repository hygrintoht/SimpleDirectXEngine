#include "physicsMeshObject.h"

#include "physicsComponent.h"
#include "quaternion.h"

physicsMeshObject::physicsMeshObject(std::string name) : meshObject(name, "cube.obj")
{
	m_unity_game_object_type = physics_cube_object;
	setPosition(vector3(0.0f, 5.0f, 0.0f));
	setScale(vector3(1.0f, 1.0f, 1.0f));
	changeAnimationType(-1);
	this->attachComponent(new physicsComponent("PhysicsComponent", this));
}

physicsMeshObject::physicsMeshObject(std::string name, vector3 position, vector3 scale, vector3 rotation) : meshObject(name, "cube.obj")
{
	m_unity_game_object_type = physics_cube_object;
	setPosition(position);
	setScale(scale);
	setRotation(rotation);
	changeAnimationType(-1);
	this->attachComponent(new physicsComponent("PhysicsComponent", this));
}

physicsMeshObject::physicsMeshObject(std::string name, vector3 position, vector3 scale, quaternion rotation) : meshObject(name, "cube.obj")
{
	m_unity_game_object_type = physics_cube_object;
	this->setMatrix(position, scale, rotation);
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