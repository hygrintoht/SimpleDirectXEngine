#pragma once
#include "component.h"
#include "vector3.h"

#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;

class physicsComponent : public component
{
public:
	physicsComponent(std::string name, gameObject* owner);
	~physicsComponent() override;

	void perform(float deltaTime) override;

	bool getGravityEnabled();
	void toggleGravity();
	void addForce();

	float getMass();
	void setMass(float mass);

	RigidBody* getRigidBody();

private:
	float m_mass = 1000.0f;
	RigidBody* m_rigidBody;

	vector3 m_scale; // local scale

	bool m_gravity_enabled = true;
};
