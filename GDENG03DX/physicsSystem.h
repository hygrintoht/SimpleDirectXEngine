#pragma once

#include "unordered_map"
#include "vector"

#include "reactphysics3d/reactphysics3d.h"

//#include "baseComponentSystem.h"

class physicsComponent;

using namespace reactphysics3d;

class physicsSystem
{
public:
	physicsSystem();
	~physicsSystem();

	void registerComponent(physicsComponent* component); // unfinished
	void unregisterComponent(physicsComponent* component); // unfinished
	void unregisterComponent(std::string name); // unfinished
	physicsComponent* findComponentByName(std::string name); // unfinished
	std::vector<physicsComponent*> getAllComponents();

	void updateAllComponents(); // unfinished
	void timeStep();

	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	std::unordered_map<std::string, physicsComponent*> m_componentTable;
	std::vector<physicsComponent*> m_componentList;

	PhysicsCommon* m_physicsCommon;
	PhysicsWorld* m_physicsWorld;
};
