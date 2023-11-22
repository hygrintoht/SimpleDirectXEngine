#pragma once
#include "component.h"

#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;

class physicsComponent : public component
{
public:
	physicsComponent(std::string name, gameObject* owner);
	~physicsComponent();

	void perform(float deltaTime) override;

	RigidBody* getRigidBody();

private:
	float m_mass = 1000.0f;
	RigidBody* m_rigidBody;
};
