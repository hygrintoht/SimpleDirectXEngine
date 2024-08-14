#include "physicsPlaneObject.h"

#include "physicsComponent.h"
#include "quaternion.h"

physicsPlaneObject::physicsPlaneObject(std::string name) : meshObject(name, "cube.obj")
{
	m_unity_game_object_type = physics_plane_object;
	setPosition(vector3(0.0f, -10.0f, 0.0f));
	setScale(vector3(10.0f, 0.2f, 10.0f));
	changeAnimationType(-1);

	this->attachComponent(new physicsComponent("PhysicsComponent", this));

	physicsComponent* component = (physicsComponent*)this->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
	component->getRigidBody()->setType(BodyType::KINEMATIC);
}

physicsPlaneObject::physicsPlaneObject(std::string name, vector3 position, vector3 scale, vector3 rotation) : meshObject(name, "cube.obj")
{
	m_unity_game_object_type = physics_plane_object;
	setPosition(position);
	setScale(scale);
	//setRotation(rotation);
	changeAnimationType(-1);
	this->attachComponent(new physicsComponent("PhysicsComponent", this));

	physicsComponent* component = (physicsComponent*)this->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
	component->getRigidBody()->setType(BodyType::KINEMATIC);
}

physicsPlaneObject::physicsPlaneObject(std::string name, vector3 position, vector3 scale, quaternion rotation) : meshObject(name, "cube.obj")
{
	m_unity_game_object_type = physics_plane_object;
	this->setMatrix(position, scale, rotation);

	changeAnimationType(-1);
	this->attachComponent(new physicsComponent("PhysicsComponent", this));

	physicsComponent* component = (physicsComponent*)this->findComponentOfType(component::componentType::Physics, "PhysicsComponent");
	component->getRigidBody()->setType(BodyType::KINEMATIC);
}

physicsPlaneObject::~physicsPlaneObject()
{
	meshObject::~meshObject();
}

void physicsPlaneObject::update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left)
{
	meshObject::update(world_camera_temp, top, bottom, right, left);
}