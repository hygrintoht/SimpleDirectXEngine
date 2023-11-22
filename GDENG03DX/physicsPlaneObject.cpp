#include "physicsPlaneObject.h"

#include "physicsComponent.h"

physicsPlaneObject::physicsPlaneObject(std::string name, bool skipInit) : meshObject(name, "cube.obj")
{
	setPosition(vector3(0.0f, -5.0f, 0.0f));
	setScale(vector3(32.0f, 0.2f, 32.0f));
	changeAnimationType(-1);
	//m_transform.setRotation(vector3(0.0f, 0.0f, 0.0f));
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